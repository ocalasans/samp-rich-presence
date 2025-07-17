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

#include <utility>
//
#include "server_manager.hpp"
#include "constants.hpp"

Server_Manager::Server_Manager(std::string ip, int port, std::string name) : server_ip(std::move(ip)),
    server_port(port),
    player_name(std::move(name)),
    connection_status(false),
    live_server_data{},
    display_server_data{},
    display_image_url(Constants::DEFAULT_IMAGE),
    current_display_social{},
    last_successful_query{},
    last_api_update{},
    last_social_rotation{},
    network_manager(),
    server_query(network_manager),
    url_manager() {}

bool Server_Manager::Initialize() {
    if (!network_manager.Initialize(server_ip, server_port))
        return false;

    Update();

    return true;
}

void Server_Manager::Fetch_API_Data() {
    display_image_url = url_manager.Get_Image_URL_And_Populate_Socials(server_ip, server_port, live_server_data);

    last_api_update = std::chrono::steady_clock::now();
    current_social_index_ = 0;

    Rotate_Social_Link();
}

void Server_Manager::Rotate_Social_Link() {
    if (!live_server_data.Social_Links.empty()) {
        if (current_social_index_ >= live_server_data.Social_Links.size())
            current_social_index_ = 0;

        current_display_social = live_server_data.Social_Links[current_social_index_];
        current_social_index_ = (current_social_index_ + 1) % live_server_data.Social_Links.size();
    }
    else
        current_display_social = {};

    last_social_rotation = std::chrono::steady_clock::now();
}

void Server_Manager::Update() {
    const auto now = std::chrono::steady_clock::now();

    if (server_query.Query(live_server_data)) {
        if (!connection_status) {
            connection_status = true;
            Fetch_API_Data();
        }

        last_successful_query = now;

        display_server_data.Hostname = live_server_data.Hostname;
        display_server_data.Players = live_server_data.Players;
        display_server_data.Max_Players = live_server_data.Max_Players;
        display_server_data.Server_Address = server_ip + ":" + std::to_string(server_port);

        if (now - last_api_update > Constants::IMAGE_UPDATE_INTERVAL)
            Fetch_API_Data();

        if (now - last_social_rotation > Constants::SOCIAL_UPDATE_INTERVAL)
            Rotate_Social_Link();
    }
    else {
        if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
            connection_status = false;
            display_image_url = Constants::DEFAULT_IMAGE;
            display_server_data = {};
            current_display_social = {};
        }
    }
}