module;

#include "Formation.hpp"

export module FatPound.Traits.Formation;

export namespace fatpound
{
    using traits::ClassOrStruct;
    using traits::Union;

#if __cplusplus >= 202302L
    using traits::ScopedEnum;
#endif

    using traits::Enum;
    using traits::Instantiable;

    using traits::AllOfIs;
    using traits::AnyOfIs;
    using traits::NoneOfIs;
}

// module : private;
