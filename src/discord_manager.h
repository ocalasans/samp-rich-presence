#ifndef DISCORD_MANAGER_H
    #define DISCORD_MANAGER_H

    #include <string_view>
    #include <ctime>
    #include "discord/discord_rpc.h"
    #include "server_types.h"

    class Discord_Manager {
        public:
            Discord_Manager() noexcept;
            void Initialize() noexcept;
            void Update_Presence(const Server_Information& server_info, std::string_view player_name, std::string_view current_image, bool is_connected) noexcept;
            void Shutdown() noexcept;
        private:
            time_t start_timestamp;
    };
#endif