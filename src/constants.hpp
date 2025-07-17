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

#include <chrono>

namespace Constants {
    // ASI Information
    inline constexpr char ASI_VERSION[] = "1.1";

    // ASI Update Information
    inline constexpr wchar_t UPDATE_API_HOST[] = L"api.github.com";
    inline constexpr wchar_t UPDATE_API_PATH[] = L"/repos/ocalasans/samp-rich-presence/releases/latest";
    inline constexpr wchar_t UPDATE_RELEASES_URL[] = L"https://github.com/ocalasans/samp-rich-presence/releases/latest";

    // Command Line Defaults
    inline constexpr char DEFAULT_SERVER_IP[] = "127.0.0.1";
    inline constexpr int DEFAULT_SERVER_PORT = 7777;

    // Discord Presence
    inline constexpr char DEFAULT_IMAGE[] = "https://raw.githubusercontent.com/ocalasans/samp-rich-presence/main/images/default_logo.png";
    inline constexpr char SOCIAL_ICON_BASE_URL[] = "https://raw.githubusercontent.com/ocalasans/samp-rich-presence/main/images/";

    // SA-MP Server Query
    inline constexpr int QUERY_TIMEOUT_MS = 800;
    inline constexpr int QUERY_PACKET_SIZE = 11;
    inline constexpr int QUERY_BUFFER_SIZE = 2048;
    inline constexpr int MAX_RETRY_ATTEMPTS = 3;

    // Update Timings
    inline constexpr std::chrono::seconds MAIN_LOOP_INTERVAL = std::chrono::seconds(1);
    inline constexpr std::chrono::minutes IMAGE_UPDATE_INTERVAL = std::chrono::minutes(5);
    inline constexpr std::chrono::seconds SOCIAL_UPDATE_INTERVAL = std::chrono::seconds(30);
}