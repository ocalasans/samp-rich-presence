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

#include <span>
#include <string>
//
#include "server_types.hpp"
#include "samp_network.hpp"

class Server_Query {
    public:
        explicit Server_Query(Samp_Network& network) noexcept;

        bool Query(Server_Information& server_data) noexcept;
    private:
        bool Try_Query(Server_Information& server_data) noexcept;
        void Assemble_Query_Packet(std::span<char> packet) const noexcept;
        static bool Parse_Response(std::span<const char> response_buffer, Server_Information& server_data) noexcept;

        template<typename T>
        static bool Read_From_Span(std::span<const char>& s, T& value) noexcept;
        static bool Read_String_From_Span(std::span<const char>& s, std::string& str) noexcept;

        Samp_Network& network_manager;
        static constexpr char QUERY_SIGNATURE[] = "SAMP";
};