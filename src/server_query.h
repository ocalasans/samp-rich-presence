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