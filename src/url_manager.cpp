/*
 * SA-MP Rich Presence - ASI for SA-MP (San Andreas Multiplayer)
 * Copyright (c) Calasans
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include "url_manager.h"
#include "constants.h"

URL_Manager::URL_Manager() : session_handle(nullptr) {
    session_handle = WinHttpOpen(L"SA-MP Rich Presence", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
}

URL_Manager::~URL_Manager() {
    if (session_handle)
        WinHttpCloseHandle(session_handle);
}

std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
    if (!session_handle)
        return Constants::DEFAULT_IMAGE;

    std::string formatted_address = server_address;
    size_t colon_pos = formatted_address.find(':');

    if (colon_pos != std::string::npos)
        formatted_address.replace(colon_pos, 1, "-");

    std::string image_url;

    if (!Get_URL_From_File(formatted_address, image_url) || image_url.empty())
        return Constants::DEFAULT_IMAGE;

    return image_url;
}

std::string URL_Manager::Parse_JSON(const std::string& json_content) {
    const std::string key = "\"spc_integration_image\":";
    size_t key_pos = json_content.find(key);

    if (key_pos == std::string::npos)
        return "";

    size_t value_start = json_content.find("\"", key_pos + key.length());

    if (value_start == std::string::npos)
        return "";

    value_start++;
    size_t value_end = json_content.find("\"", value_start);

    if (value_end == std::string::npos)
        return "";

    return json_content.substr(value_start, value_end - value_start);
}

bool URL_Manager::Get_URL_From_File(const std::string& server_address, std::string& image_url) {
    if (!session_handle)
        return false;

    HINTERNET connect = WinHttpConnect(session_handle, BASE_HOST, INTERNET_DEFAULT_HTTPS_PORT, 0);

    if (!connect)
        return false;

    std::wstring file_path = BASE_PATH;
    file_path += std::wstring(server_address.begin(), server_address.end());
    file_path += L".json";

    HINTERNET request = WinHttpOpenRequest(connect, L"GET", file_path.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

    if (!request)
        return (WinHttpCloseHandle(connect), false);

    bool success = WinHttpSendRequest(request, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0) && WinHttpReceiveResponse(request, NULL);

    if (!success) {
        WinHttpCloseHandle(request);
        WinHttpCloseHandle(connect);

        return false;
    }

    DWORD status_code = 0;
    DWORD status_code_size = sizeof(status_code);

    if (WinHttpQueryHeaders(request, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, NULL, &status_code, &status_code_size, NULL)) {
        if (status_code != 200) {
            WinHttpCloseHandle(request);
            WinHttpCloseHandle(connect);

            return false;
        }
    }

    std::string buffer;
    DWORD bytes_available;
    DWORD bytes_read;
    char temp_buffer[4096];

    do {
        bytes_available = 0;

        if (!WinHttpQueryDataAvailable(request, &bytes_available))
            break;

        if (bytes_available == 0)
            break;

        if (bytes_available > sizeof(temp_buffer))
            bytes_available = sizeof(temp_buffer);

        if (!WinHttpReadData(request, temp_buffer, bytes_available, &bytes_read))
            break;

        buffer.append(temp_buffer, bytes_read);
    }
    while (bytes_available > 0);

    WinHttpCloseHandle(request);
    WinHttpCloseHandle(connect);

    if (!buffer.empty()) {
        buffer.erase(0, buffer.find_first_not_of(" \n\r\t"));
        buffer.erase(buffer.find_last_not_of(" \n\r\t") + 1);

        image_url = Parse_JSON(buffer);

        return !image_url.empty();
    }

    return false;
}