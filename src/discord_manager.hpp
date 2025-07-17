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