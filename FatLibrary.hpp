#pragma once

#include "Automata/Automata.hpp"
#include "Bitwise/Bitwise.hpp"
#include "Concurrency/TaskQueue.hpp"
#include "DSA/DSA.hpp"
#include "File/File.hpp"
#include "IO/IO.hpp"
#include "Math/Math.hpp"
#include "Random/Random.hpp"
#include "Util/Util.hpp"

#if defined(_MSC_VER) and not defined(__clang__) and not defined(__GNUC__)
#include "Win32_/Win32_.hpp"
#endif
