#pragma once

#include <cstdint>

#include <string>
#include <utility>
#include <filesystem>

namespace fatpound::file
{
    auto GetNameAndExtension (const std::filesystem::path& path) -> std::pair<std::string, std::string>;

    void EncryptDecrypt      (const std::filesystem::path& in_path, const std::size_t& key, std::filesystem::path out_path = {});
    void EncryptDecrypt_Dir  (const std::filesystem::path& in_path, const std::size_t& key, const bool recurse = false);
    
    namespace details
    {
        void EncryptDecrypt_     (const std::filesystem::path& in_path, const std::size_t& key, std::filesystem::path& out_path);
    }
}
