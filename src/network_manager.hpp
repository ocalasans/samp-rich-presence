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

#ifndef NETWORK_MANAGER_H
    #define NETWORK_MANAGER_H

    #include <string_view>
    #include <winsock2.h>
    #include <ws2tcpip.h>

    class Network_Manager {
        public:
            Network_Manager() noexcept;
            ~Network_Manager();
            Network_Manager(const Network_Manager&) = delete;
            Network_Manager& operator=(const Network_Manager&) = delete;

            bool Initialize(std::string_view ip, int port) noexcept;
            bool Send_Query(const char* query_packet, char* response_buffer, int* received_bytes) noexcept;
        private:
            SOCKET network_socket;
            sockaddr_in server_address;
            void Cleanup() noexcept;
    };
#endif