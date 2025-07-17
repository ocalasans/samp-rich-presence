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

#include <stdexcept>
//
#include "command_line_parser.hpp"
#include "constants.hpp"
#include "utils.hpp"

bool Command_Line_Parser::Parse(const std::wstring_view command_line, std::string& server_ip, int& server_port, std::string& player_name) {
    server_ip = Constants::DEFAULT_SERVER_IP;
    server_port = Constants::DEFAULT_SERVER_PORT;

    if (const auto ip_param = Parse_Parameter(command_line, L"-h"); !ip_param.empty())
        server_ip = Utils::Convert_Wide_To_Utf8_String(ip_param);

    if (const auto port_param = Parse_Parameter(command_line, L"-p"); !port_param.empty()) {
        try {
            server_port = std::stoi(std::wstring(port_param));
        }
        catch (const std::invalid_argument&) {}
        catch (const std::out_of_range&) {}
    }

    if (const auto name_param = Parse_Parameter(command_line, L"-n"); !name_param.empty())
        player_name = Utils::Convert_Wide_To_Utf8_String(name_param);

    return !server_ip.empty() && server_port > 0 && !player_name.empty();
}

std::wstring Command_Line_Parser::Parse_Parameter(const std::wstring_view command_string, const std::wstring_view parameter) {
    if (const size_t position = command_string.find(parameter); position != std::wstring_view::npos) {
        size_t value_start = position + parameter.length();

        value_start = command_string.find_first_not_of(L" \t", value_start);

        if (value_start == std::wstring_view::npos)
            return L"";

        const size_t value_end = command_string.find(L' ', value_start);

        return std::wstring(command_string.substr(value_start, value_end - value_start));
    }

    return L"";
}