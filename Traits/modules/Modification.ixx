module;

#include "Modification.hpp"

export module FatPound.Traits.Modification;

export namespace fatpound
{
    using traits::Append;
    using traits::Append_t;
    using traits::AppendItem;
    using traits::AppendItem_t;
    using traits::AppendUnique;
    using traits::AppendUnique_t;
    using traits::AppendItemUnique;
    using traits::AppendItemUnique_t;

    using traits::Prepend;
    using traits::Prepend_t;
    using traits::PrependItem;
    using traits::PrependItem_t;
    using traits::PrependUnique;
    using traits::PrependUnique_t;
    using traits::PrependItemUnique;
    using traits::PrependItemUnique_t;

    using traits::Reverse;
    using traits::Reverse_t;

    using traits::ReverseItem;
    using traits::ReverseItem_t;

    using traits::FindIfItem;
    using traits::FindIfItem_v;

    using traits::CountIfItem;
    using traits::CountIfItem_v;

    using traits::MinItem;
    using traits::MinItem_v;
    using traits::MaxItem;
    using traits::MaxItem_v;
}

// module : private;
