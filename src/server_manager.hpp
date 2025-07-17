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

#ifndef SERVER_MANAGER_H
    #define SERVER_MANAGER_H

    #include <string>
    #include <chrono>
    #include "server_types.h"
    #include "network_manager.h"
    #include "server_query.h"
    #include "url_manager.h"

    class Server_Manager {
        public:
            Server_Manager(const std::string& ip, int port, const std::string& name);
            ~Server_Manager();

            bool Initialize();
            bool Update();
            bool Is_Connected() const { return connection_status; }
            const Server_Information& Get_Info() const { return server_data; }
            std::string Get_Player_Name() const { return player_name; }
            std::string Get_Server_Address() const { return server_ip + ":" + std::to_string(server_port); }
            std::string Get_Current_Image() const { return current_image_url; }
        private:
            bool connection_status;
            std::string server_ip;
            int server_port;
            std::string player_name;
            std::string current_image_url;
            Server_Information server_data;
            std::chrono::steady_clock::time_point last_successful_query;

            Network_Manager network_manager;
            Server_Query server_query;
            URL_Manager url_manager;
    };
#endif