#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/Core.hpp>

#include <type_traits>

namespace fatpound::win32
{
    auto ModuleHandleOfA(const LPCSTR  cstr = nullptr) -> HINSTANCE;
    auto ModuleHandleOfW(const LPCWSTR cstr = nullptr) -> HINSTANCE;



    /// @brief Retrieves a module handle for the specified module name, or throws an exception if the handle cannot be obtained
    /// 
    /// @param cstr: A pointer to a null-terminated string specifying the module name. If nullptr, returns a handle to the file used to create the calling process
    /// 
    /// @return HINSTANCE if successful
    /// 
    auto ModuleHandleOf(const std::conditional_t<UNICODE, LPCWSTR, LPCSTR>& cstr = nullptr) -> HINSTANCE;
}

#endif
