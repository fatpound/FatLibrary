module;

#include "../include/Common.hpp"

export module FatPound.Memory.Common;

export namespace fatpound
{
    using memory::AlignedUniquePtr;
    using memory::AlignedAlloc;
    using memory::MakeAlignedUniquePtr;
    using memory::AlignedFree;
}

// module : private;
