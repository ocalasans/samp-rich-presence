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

#include <string>
//
#include "discord_manager.hpp"
#include "secrets.hpp"
#include "constants.hpp"

Discord_Manager::Discord_Manager() noexcept = default;

void Discord_Manager::Initialize() noexcept {
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));

    auto app_id_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_Discord_App_ID());
    Discord_Initialize(app_id_accessor.Get(), &handlers, 1, nullptr);

    start_timestamp_ = time(nullptr);
}

void Discord_Manager::Update_Presence(const Server_Information& server_info, const server_types::Social_Link& social_link, const std::string_view player_name, const std::string_view current_image, const bool is_connected) noexcept {
    DiscordRichPresence discord_presence;
    memset(&discord_presence, 0, sizeof(discord_presence));

    discord_presence.startTimestamp = start_timestamp_;
    discord_presence.largeImageKey = current_image.data();

    if (is_connected) {
        discord_presence.details = server_info.Hostname.c_str();

        discord_presence.state = player_name.data();
        discord_presence.largeImageText = server_info.Server_Address.c_str();
        discord_presence.partySize = server_info.Players;
        discord_presence.partyMax = server_info.Max_Players;
        discord_presence.joinSecret = server_info.Server_Address.c_str();

        if (!social_link.first.empty()) {
            current_small_image_key_ = Constants::SOCIAL_ICON_BASE_URL;
            current_small_image_key_ += social_link.first;
            current_small_image_key_ += ".png";
            discord_presence.smallImageKey = current_small_image_key_.c_str();
            discord_presence.smallImageText = social_link.second.c_str();
        }
    }
    else {
        discord_presence.details = "SA-MP";
        discord_presence.state = "Idle";
        discord_presence.largeImageText = "San Andreas Multiplayer";
    }

    Discord_UpdatePresence(&discord_presence);
}

void Discord_Manager::Shutdown() noexcept {
    Discord_Shutdown();
}