#include "discord_manager.h"
#include <windows.h>

Discord_Manager::Discord_Manager() noexcept : start_timestamp(0) {}

void Discord_Manager::Initialize() noexcept {
    Sleep(5000);

    DiscordEventHandlers discord_handlers{};
    Discord_Initialize("DISCORD_APP_ID", &discord_handlers, 1, NULL); // "DISCORD_APP_ID > Application ID"

    start_timestamp = time(nullptr);
}

void Discord_Manager::Update_Presence(const Server_Information& server_info, std::string_view player_name, std::string_view current_image, bool is_connected) noexcept {
    DiscordRichPresence discord_presence{};

    if (!is_connected) {
        discord_presence.state = player_name.data();
        discord_presence.details = "SA-MP";
        discord_presence.largeImageKey = current_image.data();
        discord_presence.startTimestamp = start_timestamp;

        Discord_UpdatePresence(&discord_presence);

        return;
    }

    discord_presence.state = player_name.data();
    discord_presence.details = server_info.Hostname.c_str();
    discord_presence.largeImageKey = current_image.data();
    discord_presence.largeImageText = server_info.Server_Address.c_str();
    discord_presence.startTimestamp = start_timestamp;
    discord_presence.partySize = server_info.Players;
    discord_presence.partyMax = server_info.Max_Players;

    Discord_UpdatePresence(&discord_presence);
}

void Discord_Manager::Shutdown() noexcept {
    Discord_Shutdown();
}