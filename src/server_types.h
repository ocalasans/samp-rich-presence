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