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

#include <utility>
//
#include "samp_network.hpp"
#include "constants.hpp"

Samp_Network::Samp_Network() noexcept : network_socket(INVALID_SOCKET) {
    Reset();
}

Samp_Network::~Samp_Network() {
    Cleanup();
}

Samp_Network::Samp_Network(Samp_Network&& other) noexcept : network_socket(other.network_socket), server_address(other.server_address) {
    other.Reset();
}

Samp_Network& Samp_Network::operator=(Samp_Network&& other) noexcept {
    if (this != &other) {
        Cleanup();

        network_socket = other.network_socket;
        server_address = other.server_address;

        other.Reset();
    }

    return *this;
}

void Samp_Network::Reset() noexcept {
    network_socket = INVALID_SOCKET;
    memset(&server_address, 0, sizeof(server_address));
}

bool Samp_Network::Initialize(const std::string_view ip, const int port) noexcept {
    if (network_socket != INVALID_SOCKET)
        closesocket(network_socket);

    network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (network_socket == INVALID_SOCKET)
        return false;

    const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
    setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
    setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(static_cast<u_short>(port));
    inet_pton(AF_INET, ip.data(), &server_address.sin_addr);

    return true;
}

bool Samp_Network::Send_Query(const std::span<const char> query_packet, std::span<char> response_buffer, int& received_bytes) noexcept {
    if (sendto(network_socket, query_packet.data(), static_cast<int>(query_packet.size()), 0, reinterpret_cast<const sockaddr*>(&server_address), sizeof(server_address)) < 0)
        return false;

    sockaddr_in from_address;
    int address_length = sizeof(from_address);
    received_bytes = recvfrom(network_socket, response_buffer.data(), static_cast<int>(response_buffer.size()), 0, reinterpret_cast<sockaddr*>(&from_address), &address_length);

    return received_bytes > Constants::QUERY_PACKET_SIZE;
}

void Samp_Network::Cleanup() noexcept {
    if (network_socket != INVALID_SOCKET) {
        closesocket(network_socket);
        network_socket = INVALID_SOCKET;
    }
}