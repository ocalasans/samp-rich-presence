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

#ifndef URL_MANAGER_H
    #define URL_MANAGER_H

    #include <string>
    #include <winsock2.h>
    #include <winhttp.h>

    #pragma comment(lib, "winhttp.lib")

    class URL_Manager {
        public:
            URL_Manager();
            ~URL_Manager();

            std::string Get_Image_URL(const std::string& server_address);
        private:
            bool Get_URL_From_File(const std::string& server_address, std::string& image_url);
            std::string Parse_JSON(const std::string& json_content);

            HINTERNET session_handle;
            static constexpr wchar_t BASE_HOST[] = L"example_site.com";
            static constexpr wchar_t BASE_PATH[] = L"/example_directory/";
    };
#endif