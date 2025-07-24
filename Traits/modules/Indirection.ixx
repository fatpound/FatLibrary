module;

#include "Indirection.hpp"

export module FatPound.Traits.Indirection;

export namespace fatpound
{
    using traits::MemberPointer;
    using traits::MemberFunctionPointer;
    using traits::MemberObjectPointer;
    using traits::NonMemberPointer;
    using traits::Pointer;
    using traits::LValueReference;
    using traits::RValueReference;
    using traits::Reference;
}

// module : private;
