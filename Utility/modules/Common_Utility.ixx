module;

#include "../include/Common.hpp"

export module FatPound.Utility.Common;

export namespace fatpound
{
    using utility::BinDigits;
    using utility::OctDigits;
    using utility::DecDigits;
    using utility::HexDigits;
    using utility::BinaryDigits;
    using utility::OctalDigits;
    using utility::DecimalDigits;
    using utility::HexadecimalDigits;

    using utility::ClockHandsAngle;
    using utility::Map;
    using utility::ParseLineToIntegralVector;
    using utility::StrRev;
    using utility::StrSet;

#ifdef FATLIB_BUILDING_WITH_MSVC
    using utility::To_WString;
#endif

    using utility::ToHexString;
}

// module : private;
