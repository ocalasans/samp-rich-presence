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

#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
#include <winhttp.h>
#include <shellapi.h>

#pragma comment(lib, "winhttp.lib")
#pragma comment(lib, "shell32.lib")
//
#include "libraries/nlohmann/json.hpp"
//
#include "constants.hpp"

namespace Asi_Update {
    inline bool Check_For_Update() {
        HINTERNET h_session = nullptr, h_connect = nullptr, h_request = nullptr;
        bool update_found_and_handled = false;

        try {
            h_session = WinHttpOpen(L"SA-MP Rich Presence Update/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

            if (!h_session)
                throw std::runtime_error("WinHttpOpen failed");

            h_connect = WinHttpConnect(h_session, Constants::UPDATE_API_HOST, INTERNET_DEFAULT_HTTPS_PORT, 0);

            if (!h_connect)
                throw std::runtime_error("WinHttpConnect failed");

            h_request = WinHttpOpenRequest(h_connect, L"GET", Constants::UPDATE_API_PATH, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

            if (!h_request)
                throw std::runtime_error("WinHttpOpenRequest failed");

            if (!WinHttpSendRequest(h_request, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0) || !WinHttpReceiveResponse(h_request, NULL))
                throw std::runtime_error("WinHttpSendRequest/ReceiveResponse failed");

            std::string response_body;
            DWORD dw_size = 0;

            while (WinHttpQueryDataAvailable(h_request, &dw_size) && dw_size > 0) {
                std::vector<char> buffer(dw_size);
                DWORD dw_read;

                if (WinHttpReadData(h_request, buffer.data(), dw_size, &dw_read))
                    response_body.append(buffer.begin(), buffer.begin() + dw_read);
            }

            nlohmann::json release_info = nlohmann::json::parse(response_body);

            if (!release_info.is_object() || !release_info.contains("tag_name"))
                throw std::runtime_error("Invalid JSON response");

            std::string latest_tag = release_info["tag_name"].get<std::string>();

            if (!latest_tag.empty() && (latest_tag[0] == 'v' || latest_tag[0] == 'V'))
                latest_tag.erase(0, 1);

            int current_major = 0, current_minor = 0;
            int latest_major = 0, latest_minor = 0;
            int parse_current_ok, parse_latest_ok;

#if defined(_MSC_VER)
            parse_current_ok = sscanf_s(Constants::ASI_VERSION, "%d.%d", &current_major, &current_minor) == 2;
            parse_latest_ok = sscanf_s(latest_tag.c_str(), "%d.%d", &latest_major, &latest_minor) == 2;
#else
            parse_current_ok = sscanf(Constants::ASI_VERSION, "%d.%d", &current_major, &current_minor) == 2;
            parse_latest_ok = sscanf(latest_tag.c_str(), "%d.%d", &latest_major, &latest_minor) == 2;
#endif

            if (!parse_current_ok || !parse_latest_ok)
                throw std::runtime_error("Failed to parse version strings");

            if (latest_major > current_major || (latest_major == current_major && latest_minor > current_minor)) {
                update_found_and_handled = true;

                std::wstringstream message_stream;
                message_stream << "A new version of SA-MP Rich Presence is available!\n\n"
                    << "  Your version: v" << Constants::ASI_VERSION << "\n"
                    << "  Latest version: v" << latest_tag.c_str() << "\n\n"
                    << "Would you like to go to the download page now?\n\n"
                    << "  - 'Yes' will open your browser to download the update.\n"
                    << "  - 'No' will disable SA-MP Rich Presence. The game will start, but the ASI will not run.";

                int msgbox_result = MessageBoxW(NULL, message_stream.str().c_str(), L"SA-MP Rich Presence - Update Available", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);

                if (msgbox_result == IDYES)
                    ShellExecuteW(NULL, L"open", Constants::UPDATE_RELEASES_URL, NULL, NULL, SW_SHOWNORMAL);
            }
        }
        catch (const std::exception&) {}

        if (h_request)
            WinHttpCloseHandle(h_request);

        if (h_connect)
            WinHttpCloseHandle(h_connect);

        if (h_session)
            WinHttpCloseHandle(h_session);

        return update_found_and_handled;
    }
}