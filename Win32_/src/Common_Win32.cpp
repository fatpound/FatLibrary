#include "../include/Common.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <stdexcept>

namespace fatpound::win32
{
    auto ModuleHandleOfA(const LPCSTR cstr) -> HINSTANCE
    {
        if (const auto& hInstance{ GetModuleHandleA(cstr) }; hInstance not_eq nullptr)
        {
            return hInstance;
        }

        throw std::runtime_error("Error occured when obtaining hInstance [GetModuleHandle]");
    }
    auto ModuleHandleOfW(const LPCWSTR cstr) -> HINSTANCE
    {
        if (const auto& hInstance{ GetModuleHandleW(cstr) }; hInstance not_eq nullptr)
        {
            return hInstance;
        }

        throw std::runtime_error("Error occured when obtaining hInstance [GetModuleHandle]");
    }



    /// @brief Retrieves a module handle for the specified module name, or throws an exception if the handle cannot be obtained
    /// 
    /// @param cstr: A pointer to a null-terminated string specifying the module name. If nullptr, returns a handle to the file used to create the calling process
    /// 
    /// @return HINSTANCE if successful
    /// 
    auto ModuleHandleOf(const std::conditional_t<UNICODE, LPCWSTR, LPCSTR>& cstr) -> HINSTANCE
    {
#ifdef UNICODE
        return ModuleHandleOfW(cstr);
#else
        return ModuleHandleOfA(cstr);
#endif
    }
}

#endif
