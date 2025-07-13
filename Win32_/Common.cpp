#include <Win32_/Common.hpp>

#include <stdexcept>

namespace fatpound::win32
{
    auto ModuleHandleOf(const
#ifdef UNICODE
        LPCWSTR&
#else
        LPCSTR&
#endif
        cstr) -> HINSTANCE
    {
        if (const auto& hInstance{ ::GetModuleHandle(cstr) }; hInstance not_eq nullptr)
        {
            return hInstance;
        }

        throw std::runtime_error("Error occured when obtaining hInstance [GetModuleHandle]");
    }
}
