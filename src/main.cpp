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

#include <winsock2.h>
#include <windows.h>
#include <memory>
#include <thread>
#include <atomic>

#pragma comment(lib, "ws2_32.lib")
//
#include "constants.hpp"
#include "asi_update.hpp"
#include "command_line_parser.hpp"
#include "discord_manager.hpp"
#include "server_manager.hpp"

namespace {
    std::unique_ptr<Server_Manager> v_server_manager;
    std::unique_ptr<Discord_Manager> v_discord_manager;
    std::atomic<bool> is_running = true;

    void Initialize_Managers() {
        std::string server_ip, player_name;
        int server_port;

        Command_Line_Parser::Parse(GetCommandLineW(), server_ip, server_port, player_name);
        v_server_manager = std::make_unique<Server_Manager>(std::move(server_ip), server_port, std::move(player_name));

        if (!v_server_manager->Initialize())
            return (void)v_server_manager.reset();

        v_discord_manager = std::make_unique<Discord_Manager>();
        v_discord_manager->Initialize();
    }

    void Shutdown_Managers() {
        is_running = false;

        if (v_discord_manager) {
            v_discord_manager->Shutdown();
            v_discord_manager.reset();
        }

        if (v_server_manager)
            v_server_manager.reset();
    }
}

DWORD WINAPI Main_Update_Thread(LPVOID) {
    if (Asi_Update::Check_For_Update())
        return 0;

    WSAData wsa_data;

    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
        return 1;

    Initialize_Managers();

    while (is_running && v_server_manager && v_discord_manager) {
        v_server_manager->Update();

        v_discord_manager->Update_Presence(
            v_server_manager->Get_Server_Info(),
            v_server_manager->Get_Display_Social_Link(),
            v_server_manager->Get_Player_Name(),
            v_server_manager->Get_Current_Image_URL(),
            v_server_manager->Is_Connected());

        Discord_RunCallbacks();

        std::this_thread::sleep_for(Constants::MAIN_LOOP_INTERVAL);
    }

    if (v_discord_manager)
        v_discord_manager->Shutdown();

    WSACleanup();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID) {
    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);

            if (HANDLE thread = CreateThread(nullptr, 0, Main_Update_Thread, nullptr, 0, nullptr))
                CloseHandle(thread);

            break;
        case DLL_PROCESS_DETACH:
            Shutdown_Managers();

            break;
    }

    return TRUE;
}