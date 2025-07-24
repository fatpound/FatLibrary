#include "../include/Manager.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <stdexcept>

namespace fatpound::win32::com
{
    Manager::Manager(const DWORD& initFlags)
    {
        if (FAILED(CoInitializeEx(nullptr, initFlags)))
        {
            throw std::runtime_error("Failed to initialize COM!");
        }
    }
    Manager::~Manager() noexcept
    {
        CoUninitialize();
    }
}

#endif
