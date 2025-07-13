#pragma once

#include <Win32_/WinAPI.hpp>

namespace fatpound::win32
{
    /// @brief Retrieves a module handle for the specified module name, or throws an exception if the handle cannot be obtained
    /// 
    /// @param cstr: A pointer to a null-terminated string specifying the module name. If nullptr, returns a handle to the file used to create the calling process
    /// 
    /// @return HINSTANCE if successful
    /// 
    auto ModuleHandleOf(const
#ifdef UNICODE
        LPCWSTR&
#else
        LPCSTR&
#endif
        cstr = nullptr) -> HINSTANCE;
}
