#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>

#include <string>
#include <unordered_map>
#include <type_traits>

namespace fatpound::win32
{
    class MessageMap final
    {
    public:
        using String_t = std::conditional_t<UNICODE, std::wstring, std::string>;


    public:
        explicit MessageMap();
        explicit MessageMap(const MessageMap&)     = delete;
        explicit MessageMap(MessageMap&&) noexcept = delete;

        auto operator = (const MessageMap&)     -> MessageMap& = delete;
        auto operator = (MessageMap&&) noexcept -> MessageMap& = delete;
        ~MessageMap() noexcept                                 = default;


    public:
        auto operator () (const DWORD msg, const WPARAM wp, const LPARAM lp) const -> String_t;
        

    protected:


    private:
        std::unordered_map<DWORD, String_t>  m_map_;
    };
}

#endif
