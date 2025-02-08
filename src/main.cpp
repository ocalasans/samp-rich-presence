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

#include <winsock2.h>
#include <memory>
#include "server_manager.h"
#include "discord_manager.h"
#include "command_line_parser.h"
#include "constants.h"

#pragma comment(lib, "ws2_32.lib")

namespace {
    std::unique_ptr<Server_Manager> Global_Server_Manager;
    std::unique_ptr<Discord_Manager> Global_Discord_Manager;
}

DWORD WINAPI Update_Thread(LPVOID) {
    WSAData wsa_data;

    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
        return 1;

    std::string server_ip, player_name;
    int server_port;

    if (!Command_Line_Parser::Parse(GetCommandLineW(), server_ip, server_port, player_name))
        return (WSACleanup(), 1);

    Global_Server_Manager = std::make_unique<Server_Manager>(server_ip, server_port, player_name);
    Global_Discord_Manager = std::make_unique<Discord_Manager>();

    if (!Global_Server_Manager->Initialize()) {
        Global_Server_Manager.reset();
        Global_Discord_Manager.reset();
        WSACleanup();

        return 1;
    }

    Global_Discord_Manager->Initialize();

    while (true) {
        Global_Server_Manager->Update();
        Global_Discord_Manager->Update_Presence(
            Global_Server_Manager->Get_Info(),
            Global_Server_Manager->Get_Player_Name(),
            Global_Server_Manager->Get_Current_Image(),
            Global_Server_Manager->Is_Connected()
        );
        Discord_RunCallbacks();

        Sleep(Constants::PRESENCE_UPDATE_INTERVAL);
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE module_handle, DWORD reason, LPVOID) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module_handle);
            CreateThread(nullptr, 0, Update_Thread, nullptr, 0, nullptr);
            break;
        case DLL_PROCESS_DETACH:
            if (Global_Server_Manager)
                Global_Server_Manager.reset();

            if (Global_Discord_Manager) {
                Global_Discord_Manager->Shutdown();
                Global_Discord_Manager.reset();
            }

            WSACleanup();
            break;
    }

    return TRUE;
}