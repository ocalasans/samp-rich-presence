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

#include "libraries/Dralyxor/dralyxor.hpp"

namespace Secrets {
    namespace {
        inline auto& Get_Obfuscated_Discord_App_ID() {
            static auto& dc_app_id_obfuscated = DRALYXOR_KEY("DISCORD_APP_ID", "KEY_THAT_ONLY_YOU_KNOW");

            return dc_app_id_obfuscated;
        }

        inline auto& Get_Obfuscated_API_Host() {
            static auto& API_host_obfuscated = DRALYXOR_KEY("example.com", "KEY_THAT_ONLY_YOU_KNOW");

            return API_host_obfuscated;
        }

        inline auto& Get_Obfuscated_API_Path() {
            static auto& API_path_obfuscated = DRALYXOR_KEY("/path/spc-integration-api.php", "KEY_THAT_ONLY_YOU_KNOW");

            return API_path_obfuscated;
        }
    }

    namespace Detail {
        inline auto& Get_Discord_App_ID() {
            return Get_Obfuscated_Discord_App_ID();
        }

        inline auto& Get_API_Host() {
            return Get_Obfuscated_API_Host();
        }

        inline auto& Get_API_Path() {
            return Get_Obfuscated_API_Path();
        }
    }
}