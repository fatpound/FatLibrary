#pragma once

#if FAT_BUILD_ONLY_WITH_MSVC
#include <FatWin32.hpp>
#endif

#if FAT_BUILD_ONLY_WITH_MSVC

#include <string>

namespace fatpound::util
{
    static auto ToWString(const std::string& str) -> std::wstring
    {
        std::wstring wstr(str.size(), '\0');

        ::MultiByteToWideChar(
            CP_UTF8,
            0,
            str.c_str(),
            static_cast<int>(str.size()),
            wstr.data(),
            static_cast<int>(wstr.size())
        );

        return wstr;
    }
}

#endif
