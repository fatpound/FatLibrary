#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#define FATPOUND_FULL_WIN_TARGETED
#include <Win32_/include/FatWin.hpp>
#undef  FATPOUND_FULL_WIN_TARGETED
#include <winDNS.h>
#include <subauth.h>

#endif
