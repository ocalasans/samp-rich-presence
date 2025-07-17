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

#ifndef SERVER_QUERY_H
    #define SERVER_QUERY_H

    #include <string>
    #include "server_types.h"
    #include "network_manager.h"
    #include "constants.h"

    class Server_Query {
        public:
            explicit Server_Query(Network_Manager& network) noexcept;
            bool Query(Server_Information& server_data) noexcept;
        private:
            Network_Manager& network_manager;
            static bool Assemble_Query_Packet(char* packet) noexcept;
            static bool Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept;
            bool Try_Query(Server_Information& server_data, int retry_count = 0) noexcept;
            static constexpr char QUERY_SIGNATURE[] = "SAMP";
    };
#endif