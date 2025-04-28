#pragma once

#include <FatWin32.hpp>

#include <stdexcept>

namespace fatpound::win32
{
#ifdef UNICODE
    using CREATESTRUCT_t = ::CREATESTRUCTW;
    using STR_t          = ::LPCWSTR;
#else
    using CREATESTRUCT_t = ::CREATESTRUCTA;
    using STR_t          = ::LPCSTR;
#endif

    static auto ModuleHandleOf(const STR_t& cstr = nullptr) -> HINSTANCE
    {
        const auto& hInstance{ ::GetModuleHandle(cstr) };

        if (hInstance == nullptr)
        {
            throw std::runtime_error("Error occured when obtaining hInstance [GetModuleHandle]");
        }

        return hInstance;
    }
}
