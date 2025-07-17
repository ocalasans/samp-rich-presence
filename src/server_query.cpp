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

#include <thread>
#include <chrono>
#include <cstring>
#include <array>
//
#include "server_query.hpp"
#include "constants.hpp"

Server_Query::Server_Query(Samp_Network& network) noexcept : network_manager(network) {}

bool Server_Query::Query(Server_Information& server_data) noexcept {
    for (int attempt = 0; attempt < Constants::MAX_RETRY_ATTEMPTS; ++attempt) {
        if (Try_Query(server_data))
            return true;

        if (attempt < Constants::MAX_RETRY_ATTEMPTS - 1)
            std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)));
    }

    return false;
}

bool Server_Query::Try_Query(Server_Information& server_data) noexcept {
    std::array<char, Constants::QUERY_PACKET_SIZE> query_packet{};
    Assemble_Query_Packet(query_packet);

    std::array<char, Constants::QUERY_BUFFER_SIZE> response_buffer{};
    int received_bytes = 0;

    if (network_manager.Send_Query(query_packet, response_buffer, received_bytes))
        return Parse_Response({ response_buffer.data(), static_cast<size_t>(received_bytes) }, server_data);

    return false;
}

void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
    memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1);
    packet[10] = 'i';
}

template<typename T>
bool Server_Query::Read_From_Span(std::span<const char>& s, T& value) noexcept {
    if (s.size() < sizeof(T))
        return false;

    memcpy(&value, s.data(), sizeof(T));
    s = s.subspan(sizeof(T));

    return true;
}

bool Server_Query::Read_String_From_Span(std::span<const char>& s, std::string& str) noexcept {
    uint32_t length = 0;

    if (!Read_From_Span(s, length))
        return false;

    if (s.size() < length)
        return false;

    str.assign(s.data(), length);
    s = s.subspan(length);

    return true;
}

bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
    if (response.size() <= Constants::QUERY_PACKET_SIZE)
        return false;

    auto data_span = response.subspan(Constants::QUERY_PACKET_SIZE);

    [[maybe_unused]] bool passworded;

    if (!Read_From_Span(data_span, passworded))
        return false;

    if (!Read_From_Span(data_span, server_data.Players))
        return false;

    if (!Read_From_Span(data_span, server_data.Max_Players))
        return false;

    if (!Read_String_From_Span(data_span, server_data.Hostname))
        return false;

    return true;
}