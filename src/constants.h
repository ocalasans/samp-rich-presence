#ifndef CONSTANTS_H
    #define CONSTANTS_H

    namespace Constants {
        inline constexpr char DEFAULT_SERVER_IP[] = "127.0.0.1";
        inline constexpr int DEFAULT_SERVER_PORT = 7777;
        inline constexpr char DEFAULT_IMAGE[] = "https://dl.dropboxusercontent.com/scl/fi/k23e5e2myonztt57l4vrs/san-andreas-multiplayer.png?rlkey=z7mvr65vbnotpyufeq4xh2sng&st=8hummqf2&dl=0";
        inline constexpr int QUERY_TIMEOUT = 1000;
        inline constexpr int QUERY_PACKET_SIZE = 11;
        inline constexpr int QUERY_BUFFER_SIZE = 512;
        inline constexpr int MAX_RETRY_ATTEMPTS = 3;
        inline constexpr int PRESENCE_UPDATE_INTERVAL = 5000;
    }
#endif