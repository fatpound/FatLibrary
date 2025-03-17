#pragma once

#if defined(_MSC_VER) and not defined(__clang__) and not defined(__GNUC__)
#include <FatWin32.hpp>
#endif

#if defined(_MSC_VER) and not defined(__clang__) and not defined(__GNUC__)

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
