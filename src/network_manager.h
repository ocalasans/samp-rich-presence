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