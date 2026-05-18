#include "../include/Manager.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>
#include <mfapi.h>

#include <_macros/Win.hpp>
#include <Win32_/include/HrException.hpp>

#pragma comment(lib, "mfplat")

namespace fatpound::win32::mf
{
    Manager::Manager()
    {
        FAT_THROW_HRX_IF_FAILED(MFStartup(MF_VERSION), "Failed to initialize Microsoft Media Foundation!");
    }
    Manager::~Manager() noexcept
    {
        MFShutdown();
    }
}

#endif
