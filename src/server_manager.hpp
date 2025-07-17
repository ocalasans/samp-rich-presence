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

#pragma once

#include <string>
#include <chrono>
#include <memory>
//
#include "server_types.hpp"
#include "samp_network.hpp"
#include "server_query.hpp"
#include "url_manager.hpp"

class Server_Manager {
    public:
        Server_Manager(std::string ip, int port, std::string name);
        ~Server_Manager() = default;

        bool Initialize();
        void Update();

        [[nodiscard]] bool Is_Connected() const {
            return connection_status;
        }

        [[nodiscard]] const Server_Information& Get_Server_Info() const {
            return display_server_data;
        }

        [[nodiscard]] const std::string& Get_Player_Name() const {
            return player_name;
        }

        [[nodiscard]] const std::string& Get_Current_Image_URL() const {
            return display_image_url;
        }

        [[nodiscard]] const server_types::Social_Link& Get_Display_Social_Link() const {
            return current_display_social;
        }
    private:
        void Fetch_API_Data();
        void Rotate_Social_Link();

        const std::string server_ip;
        const int server_port;
        const std::string player_name;

        bool connection_status;
        Server_Information live_server_data;
        Server_Information display_server_data;
        std::string display_image_url;

        server_types::Social_Link current_display_social;
        size_t current_social_index_{0};

        std::chrono::steady_clock::time_point last_successful_query;
        std::chrono::steady_clock::time_point last_api_update;
        std::chrono::steady_clock::time_point last_social_rotation;

        Samp_Network network_manager;
        Server_Query server_query;
        URL_Manager url_manager;
};