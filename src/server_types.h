#ifndef SERVER_TYPES_H
    #define SERVER_TYPES_H

    #include <string>
    #include <cstdint>

    struct Server_Information {
        uint16_t Players{ 0 };
        uint16_t Max_Players{ 0 };
        std::string Hostname;
        std::string Server_Image;
        std::string Server_Address;
    };
#endif