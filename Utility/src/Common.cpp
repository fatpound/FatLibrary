#include "../include/Common.hpp"

namespace fatpound::utility
{
#ifdef FATLIB_BUILDING_WITH_MSVC

    auto To_WString(const std::string& str) -> std::wstring
    {
        if (str.empty())
        {
            return {};
        }

        const auto& required_size = ::MultiByteToWideChar(
            CP_UTF8,
            MB_ERR_INVALID_CHARS,
            str.c_str(),
            static_cast<int>(str.size()),
            nullptr,
            0
        );

        if (required_size == 0)
        {
            throw std::runtime_error("Failed to calculate required size for string conversion!");
        }

        std::wstring wstr(static_cast<std::size_t>(required_size), L'\0');

        const auto& bytes_written = ::MultiByteToWideChar(
            CP_UTF8,
            MB_ERR_INVALID_CHARS,
            str.c_str(),
            static_cast<int>(str.size()),
            wstr.data(),
            required_size
        );

        if (bytes_written == 0)
        {
            throw std::runtime_error("Failed to convert string to wstring!");
        }

        return wstr;
    }

#endif



    auto ToHexString(const std::uint8_t& value) -> std::string
    {
        return
        {
            HexDigits[static_cast<unsigned int>(value >> 4U) bitand 0x0FU],
            HexDigits[value bitand 0x0FU]
        };
    }
}
