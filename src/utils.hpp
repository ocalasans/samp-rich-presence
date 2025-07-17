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
#include <string_view>
#include <windows.h>

namespace Utils {
    inline std::string Convert_Wide_To_Utf8_String(const std::wstring_view wide_string) {
        if (wide_string.empty())
            return "";

        const int required_size = WideCharToMultiByte(CP_UTF8, 0, wide_string.data(), static_cast<int>(wide_string.length()), nullptr, 0, nullptr, nullptr);

        if (required_size == 0)
            return "";

        std::string result(required_size, 0);
        WideCharToMultiByte(CP_UTF8, 0, wide_string.data(), static_cast<int>(wide_string.length()), result.data(), required_size, nullptr, nullptr);

        return result;
    }

    inline std::wstring Convert_Utf8_To_Wide_String(const std::string_view narrow_string) {
        if (narrow_string.empty())
            return L"";

        const int required_size = MultiByteToWideChar(CP_UTF8, 0, narrow_string.data(), static_cast<int>(narrow_string.length()), nullptr, 0);

        if (required_size == 0)
            return L"";

        std::wstring wide_string(required_size, 0);
        MultiByteToWideChar(CP_UTF8, 0, narrow_string.data(), static_cast<int>(narrow_string.length()), wide_string.data(), required_size);

        return wide_string;
    }
}