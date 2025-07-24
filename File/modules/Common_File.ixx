module;

#include "../include/Common.hpp"

export module FatPound.File.Common;

export namespace fatpound
{
    using file::CharCount_Unchecked;
    using file::CharCount;
    using file::CharCount_Dir;
    using file::EncryptDecrypt;
    using file::EncryptDecrypt_Dir;
    using file::LineCount_Unchecked;
    using file::LineCount;
    using file::LineCount_Dir;
    using file::NameAndExtension;
    using file::ToUriPath;
    using file::PrintHex;
}

// module : private;
