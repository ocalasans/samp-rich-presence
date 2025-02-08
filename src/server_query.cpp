#include "server_query.h"
#include "constants.h"
#include <thread>
#include <chrono>

Server_Query::Server_Query(Network_Manager& network) noexcept : network_manager(network) {}

bool Server_Query::Query(Server_Information& server_data) noexcept {
    return Try_Query(server_data, Constants::MAX_RETRY_ATTEMPTS);
}

bool Server_Query::Try_Query(Server_Information& server_data, int retry_count) noexcept {
    alignas(16) char query_packet[Constants::QUERY_PACKET_SIZE] = {};

    if (!Assemble_Query_Packet(query_packet))
        return false;

    alignas(16) char response_buffer[Constants::QUERY_BUFFER_SIZE] = {};
    int received_bytes;

    for (int attempt = 0; attempt <= retry_count; attempt++) {
        if (network_manager.Send_Query(query_packet, response_buffer, &received_bytes)) {
            if (Parse_Response(response_buffer, received_bytes, server_data))
                return true;
        }

        if (attempt < retry_count)
            std::this_thread::sleep_for(std::chrono::milliseconds(100 * (attempt + 1)));
    }

    return false;
}

bool Server_Query::Assemble_Query_Packet(char* packet) noexcept {
    memcpy(packet, QUERY_SIGNATURE, 4);
    packet[10] = 'i';

    return true;
}

bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
    if (received_bytes <= Constants::QUERY_PACKET_SIZE)
        return false;

    char* current_pos = response_buffer + Constants::QUERY_PACKET_SIZE;
    const char* buffer_end = response_buffer + received_bytes;

    current_pos += sizeof(bool);

    if (current_pos + sizeof(server_data.Players) + sizeof(server_data.Max_Players) > buffer_end)
        return false;

    memcpy(&server_data.Players, current_pos, sizeof(server_data.Players));
    current_pos += sizeof(server_data.Players);
    memcpy(&server_data.Max_Players, current_pos, sizeof(server_data.Max_Players));
    current_pos += sizeof(server_data.Max_Players);

    auto read_string = [](char*& pos, const char* end, std::string& str) noexcept -> bool {
        if (pos + sizeof(uint32_t) > end)
            return false;

        uint32_t length;
        memcpy(&length, pos, sizeof(length));
        pos += sizeof(length);

        if (pos + length > end)
            return false;

        str.assign(pos, length);
        pos += length;

        return true;
    };

    if (!read_string(current_pos, buffer_end, server_data.Hostname))
        return false;

    uint32_t length;
    
    if (current_pos + sizeof(uint32_t) > buffer_end)
        return false;

    memcpy(&length, current_pos, sizeof(length));
    current_pos += sizeof(length) + length;

    if (current_pos + sizeof(uint32_t) > buffer_end)
        return false;

    memcpy(&length, current_pos, sizeof(length));
    current_pos += sizeof(length) + length;

    return true;
}