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
#include <windows.h>
#include <winhttp.h>

#pragma comment(lib, "winhttp.lib")
//
#include "server_types.hpp"

class URL_Manager {
    public:
        URL_Manager();
        ~URL_Manager();

        URL_Manager(const URL_Manager&) = delete;
        URL_Manager& operator=(const URL_Manager&) = delete;
        URL_Manager(URL_Manager&&) = delete;
        URL_Manager& operator=(URL_Manager&&) = delete;

        std::string Get_Image_URL_And_Populate_Socials(const std::string& ip, int port, Server_Information& server_info);
    private:
        std::string Request_API_Data(const std::wstring& path);
        std::string Parse_API_Response(const std::string& json_content, Server_Information& server_info);
        HINTERNET session_handle;
};