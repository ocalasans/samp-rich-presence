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

#include "network_manager.h"
#include "constants.h"
#include <cstring>

Network_Manager::Network_Manager() noexcept : network_socket(INVALID_SOCKET) {
    memset(&server_address, 0, sizeof(server_address));
}

Network_Manager::~Network_Manager() {
    Cleanup();
}

bool Network_Manager::Initialize(std::string_view ip, int port) noexcept {
    network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (network_socket == INVALID_SOCKET)
        return false;

    timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
    setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
    setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, ip.data(), &server_address.sin_addr);

    return true;
}

bool Network_Manager::Send_Query(const char* query_packet, char* response_buffer, int* received_bytes) noexcept {

    if (sendto(network_socket, query_packet, Constants::QUERY_PACKET_SIZE, 0, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) < 0)
        return false;

    sockaddr_in from_address;
    int address_length = sizeof(from_address);

    *received_bytes = recvfrom(network_socket, response_buffer, Constants::QUERY_BUFFER_SIZE, 0, reinterpret_cast<sockaddr*>(&from_address), &address_length);

    return *received_bytes > Constants::QUERY_PACKET_SIZE;
}

void Network_Manager::Cleanup() noexcept {
    if (network_socket != INVALID_SOCKET) {
        closesocket(network_socket);
        network_socket = INVALID_SOCKET;
    }
}