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

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string_view>
#include <span>

class Samp_Network {
    public:
        Samp_Network() noexcept;
        ~Samp_Network();

        Samp_Network(const Samp_Network&) = delete;
        Samp_Network& operator=(const Samp_Network&) = delete;
        Samp_Network(Samp_Network&& other) noexcept;
        Samp_Network& operator=(Samp_Network&& other) noexcept;

        bool Initialize(std::string_view ip, int port) noexcept;
        bool Send_Query(std::span<const char> query_packet, std::span<char> response_buffer, int& received_bytes) noexcept;
    private:
        void Cleanup() noexcept;
        void Reset() noexcept;

        SOCKET network_socket;
        sockaddr_in server_address;
};