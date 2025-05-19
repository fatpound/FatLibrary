#pragma once

#include <FatWin32.hpp>

#include <stdexcept>

namespace fatpound::win32
{
    static auto ModuleHandleOf(const
#ifdef UNICODE
        ::LPCWSTR
#else
        ::LPCSTR
#endif
        & cstr = nullptr) -> HINSTANCE
    {
        if (const auto& hInstance{ ::GetModuleHandle(cstr) }; hInstance not_eq nullptr)
        {
            return hInstance;
        }

        throw std::runtime_error("Error occured when obtaining hInstance [GetModuleHandle]");
    }
}
