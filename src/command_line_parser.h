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

#ifndef COMMAND_LINE_PARSER_H
    #define COMMAND_LINE_PARSER_H

    #include <string>
    #include <windows.h>

    class Command_Line_Parser {
        public:
            static bool Parse(const wchar_t* command_line, std::string& server_ip, int& server_port, std::string& player_name);
        private:
            static std::string Convert_To_String(const std::wstring& wide_string);
            static std::wstring Parse_Parameter(const std::wstring& command_string, const wchar_t* parameter);
    };
#endif