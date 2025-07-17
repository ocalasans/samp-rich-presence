/* ============================================================================= *
 * SA-MP Rich Presence - ASI for SA-MP (San Andreas Multiplayer)                 *
 * ============================================================================= *
 *                                                                               *
 * Copyright (c) 2025, Calasans | All rights reserved.                           *
 *                                                                               *
 * Developed by: Calasans                                                        *
 * Repository: https://github.com/ocalasans/samp-rich-presence                   *
 *                                                                               *
 * ============================================================================= *
 *                                                                               *
 * Licensed under the Apache License, Version 2.0 (the "License");               *
 * you may not use this file except in compliance with the License.              *
 * You may obtain a copy of the License at:                                      *
 *                                                                               *
 *     http://www.apache.org/licenses/LICENSE-2.0                                *
 *                                                                               *
 * Unless required by applicable law or agreed to in writing, software           *
 * distributed under the License is distributed on an "AS IS" BASIS,             *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.      *
 * See the License for the specific language governing permissions and           *
 * limitations under the License.                                                *
 *                                                                               *
 * ============================================================================= */

#include <vector>
#include <string>
//
#include "libraries/nlohmann/json.hpp"
//
#include "url_manager.hpp"
#include "secrets.hpp"
#include "constants.hpp"
#include "utils.hpp"

URL_Manager::URL_Manager() : session_handle(nullptr) {
    session_handle = WinHttpOpen(L"SA-MP Rich Presence/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
}

URL_Manager::~URL_Manager() {
    if (session_handle)
        WinHttpCloseHandle(session_handle);
}

std::string URL_Manager::Get_Image_URL_And_Populate_Socials(const std::string& ip, const int port, Server_Information& server_info) {
    if (!session_handle)
        return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE);

    auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
    std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
    path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
    const std::string json_data = Request_API_Data(path);

    if (json_data.empty())
        return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE);

    return Parse_API_Response(json_data, server_info);
}

std::string URL_Manager::Parse_API_Response(const std::string& json_content, Server_Information& server_info) {
    server_info.Social_Links.clear();

    try {
        const auto json = nlohmann::json::parse(json_content);

        if (json.value("success", false) && json.contains("data") && json["data"].contains("public")) {
            const auto& public_data = json["data"]["public"];
            const std::vector<std::string> social_keys = { "website", "discord", "youtube", "instagram", "facebook", "tiktok" };
            
            for (const auto& key : social_keys) {
                if (public_data.contains(key)) {
                    std::string value = public_data.value(key, "not-defined");
                    
                    if (!value.empty() && value != "not-defined")
                        server_info.Social_Links.push_back({ key, value });
                }
            }

            return public_data.value("logo", "");
        }
    }
    catch (const nlohmann::json::exception&) {}

    return "";
}

std::string URL_Manager::Request_API_Data(const std::wstring& path) {
    auto api_host_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Host());
    const std::wstring wide_host = Utils::Convert_Utf8_To_Wide_String(api_host_accessor.Get());
    HINTERNET connect_handle = WinHttpConnect(session_handle, wide_host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);

    if (!connect_handle)
        return "";

    HINTERNET request_handle = WinHttpOpenRequest(connect_handle, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

    if (!request_handle)
        return (WinHttpCloseHandle(connect_handle), "");


    if (!WinHttpSendRequest(request_handle, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0) || !WinHttpReceiveResponse(request_handle, nullptr)) {
        WinHttpCloseHandle(request_handle);
        WinHttpCloseHandle(connect_handle);

        return "";
    }

    DWORD status_code = 0;
    DWORD status_code_size = sizeof(status_code);
    WinHttpQueryHeaders(request_handle, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, nullptr, &status_code, &status_code_size, nullptr);

    if (status_code != 200) {
        WinHttpCloseHandle(request_handle);
        WinHttpCloseHandle(connect_handle);

        return "";
    }

    std::string response_body;
    std::vector<char> buffer(4096);
    DWORD bytes_available;

    while (WinHttpQueryDataAvailable(request_handle, &bytes_available) && bytes_available > 0) {
        DWORD bytes_read = 0;

        if (buffer.size() < bytes_available)
            buffer.resize(bytes_available);

        if (WinHttpReadData(request_handle, buffer.data(), bytes_available, &bytes_read))
            response_body.append(buffer.data(), bytes_read);
        else
            break;
    }

    WinHttpCloseHandle(request_handle); WinHttpCloseHandle(connect_handle);

    return response_body;
}