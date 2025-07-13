#pragma once

#include <Cryptography/XorCipher.hpp>

#include <cstdint>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <random>
#include <iterator>
#include <stdexcept>
#include <variant>
#include <filesystem>
#include <format>

#if __cplusplus >= 202302L
#include <print>
#endif

namespace fatpound::file
{
    /// @brief Counts how many times a specific character appears in a given file. Checks neither whether the path exists nor whether it refers to a regular file
    ///
    /// @tparam ForNewline: Set to true only if this function is specifically used to count newline characters
    ///
    /// @param path: The path to the file in which the character occurrences will be counted
    /// @param   ch: The character to count
    ///
    /// @return The number of times the character appears in the file
    /// 
    template <bool ForNewline = false>
    static auto CharCount_Unchecked (const std::filesystem::path& path, const char& character) -> std::size_t
    {
        std::ifstream file(path, std::ios::binary);

        if (not file.is_open())
        {
            throw std::runtime_error("Cannot open file!");
        }

        const auto& count = static_cast<std::size_t>(std::count_if<>(std::istreambuf_iterator<char>{ file }, {}, [character](const auto& ch) noexcept -> bool { return ch == character; }));

        if (ForNewline)
        {
            return count + static_cast<std::size_t>(std::filesystem::file_size(path) not_eq 0);
        }

        return count;
    }



    /// @brief Counts how many times a specific character appears in a given file.
    ///
    /// @tparam ForNewline: Set to true only if this function is specifically used to count newline characters
    ///
    /// @param path: The path to the file in which the character occurrences will be counted
    /// @param   ch: The character to count
    ///
    /// @return The number of times the character appears in the file
    /// 
    template <bool ForNewline = false>
    static auto CharCount           (const std::filesystem::path& path, const char& character) -> std::size_t
    {
        if (not std::filesystem::exists(path))
        {
            throw std::runtime_error("The given path does NOT exist!");
        }

        if (not std::filesystem::is_regular_file(path))
        {
            throw std::runtime_error("The given path is NOT a regular file!");
        }

        return CharCount_Unchecked<ForNewline>(path, character);
    }



    /// @brief Counts how many times a specific character appears in all regular files within a given directory
    /// 
    /// @tparam     ForNewline: Set to true only if this function is specifically used to count newline characters
    /// 
    /// @param            path: The path to the DIR in which the character occurrences will be counted
    /// @param       character: The character to count
    /// @param         recurse: If true, traverses subdirectories recursively; otherwise, only the top-level directory is scanned
    /// @param extensionFilter: A list of file extensions to filter which files will be read
    /// 
    /// @return The total number of times the character appears in all regular files found in the directory
    /// 
    template <bool ForNewline = false>
    static auto CharCount_Dir       (const std::filesystem::path& path, const char& character, const bool& recurse = false, const std::vector<std::string>& extensionFilter = {}) -> std::size_t
    {
        namespace fs = std::filesystem;

        if (not fs::exists(path))
        {
            throw std::runtime_error("The given path does NOT exist!");
        }

        if (not fs::is_directory(path))
        {
            throw std::runtime_error("The given path is NOT a directory!");
        }

        // NOLINTBEGIN(cppcoreguidelines-macro-usage)

        using DirIt = std::variant<fs::recursive_directory_iterator, fs::directory_iterator>;
        
        return std::visit<>(
            [&filters = extensionFilter, ch = character](auto&& it) -> std::size_t
            {
#define FATLIB_FILE_LINECOUNT_DIR_LOOP_GENERATOR(...)                               \
                                                                                    \
                for (const auto& dir_entry : it)                                    \
                {                                                                   \
                    if (fs::is_regular_file(dir_entry) __VA_ARGS__ )                \
                    {                                                               \
                        total += CharCount_Unchecked<ForNewline>(dir_entry, ch);    \
                    }                                                               \
                }

                std::size_t total{};

                if (filters.empty())
                {
                    FATLIB_FILE_LINECOUNT_DIR_LOOP_GENERATOR()
                }
                else
                {
                    FATLIB_FILE_LINECOUNT_DIR_LOOP_GENERATOR(and (std::ranges::find(filters, dir_entry.path().extension().string()) not_eq filters.cend()))
                }

                return total;

#undef FATLIB_FILE_LINECOUNT_DIR_LOOP_GENERATOR
            },
            recurse
                ? DirIt{ fs::recursive_directory_iterator{ path, fs::directory_options::skip_permission_denied } }
                : DirIt{ fs::directory_iterator          { path, fs::directory_options::skip_permission_denied } }
        );

        // NOLINTEND(cppcoreguidelines-macro-usage)
    }



    /// @brief Returns the name and extension of a regular file from a given filesystem path
    /// 
    /// @param path: The filesystem path to the file
    /// 
    /// @return A pair containing the file name (without extension) and the file extension as strings
    /// 
    auto NameAndExtension    (const std::filesystem::path& path) -> std::pair<std::string, std::string>;



    auto ToUriPath           (const std::filesystem::path& path) -> std::string;



    /// @brief Counts lines in a given file. Checks neither whether the path exists nor whether it refers to a regular file
    ///
    /// @param path: The path to the file in which the lines will be counted
    ///
    /// @return The number of lines in the file
    /// 
    auto LineCount_Unchecked (const std::filesystem::path& path) -> std::size_t;



    /// @brief Counts lines in a given file
    ///
    /// @param path: The path to the file in which the lines will be counted
    ///
    /// @return The number of lines in the file
    /// 
    auto LineCount           (const std::filesystem::path& path) -> std::size_t;



    /// @brief Counts lines in all regular files within a given directory
    /// 
    /// @param            path: The path to the DIR in which the lines will be counted
    /// @param         recurse: If true, traverses subdirectories recursively; otherwise, only the top-level directory is scanned
    /// @param extensionFilter: A list of file extensions to filter which files will be read
    /// 
    /// @return The total number of lines in all regular files found in the directory
    /// 
    auto LineCount_Dir       (const std::filesystem::path& path, const bool& recurse = false, const std::vector<std::string>& extensionFilter = {}) -> std::size_t;



    /// @brief Prints the contents of a file as hexadecimal values to the specified output stream (with spaces between those values)
    /// 
    /// @param path: The path to the file whose contents will be printed in hexadecimal format
    /// @param   os: The output stream to which the hexadecimal values will be written. Defaults to std::cout
    /// 
    void PrintHex            (const std::filesystem::path& path, std::ostream& os = std::cout);



    /// @brief Encrypts or decrypts a file and replaces the original file with the processed output
    /// 
    /// @param  inPath: The path to the input file to be encrypted or decrypted
    /// @param     key: The key used for encryption or decryption
    /// @param outPath: The path to the output file AND its name. If not specified, the file will be encrypted in-place
    /// 
    void EncryptDecrypt      (const std::filesystem::path& inPath, const std::size_t& key, std::filesystem::path outPath = {});



    /// @brief Encrypts or decrypts all regular files in a directory using a specified key
    /// 
    /// @param          inPath: The path to the input directory containing files to encrypt or decrypt
    /// @param             key: The encryption or decryption key to use
    /// @param         outPath: The output directory path where processed files will be saved. If not specified, the default behavior is used
    /// @param         recurse: If true, processes files in all subdirectories recursively; otherwise, only processes files in the top-level directory. Defaults to false
    /// @param extensionFilter: extensions as a vector of strings to filter the files that will be processed
    /// 
    void EncryptDecrypt_Dir  (const std::filesystem::path& inPath, const std::size_t& key, std::filesystem::path outPath = {}, const bool& recurse = false, const std::vector<std::string>& extensionFilter = {});
}
