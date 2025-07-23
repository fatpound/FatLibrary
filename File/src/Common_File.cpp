#include "../include/Common.hpp"

namespace fatpound::file::details
{
    /// @brief Encrypts or decrypts a file using an XOR cipher with the specified key
    /// 
    /// @param  inPath: The path to the input file to be encrypted or decrypted
    /// @param     key: The key to use for the XOR cipher
    /// @param outPath: The path where the output file will be written. If empty or the same as inPath, a temporary file path is used
    /// 
    static void EncryptDecrypt_Impl (const std::filesystem::path& inPath, const std::size_t& key, const std::filesystem::path& outPath)
    {
        std::ifstream inputFile(inPath, std::ios::binary);

        if (not inputFile.is_open())
        {
            throw std::runtime_error("Input file cannot be opened!");
        }

        std::ofstream outputFile(outPath, std::ios::binary);

        if (not outputFile.is_open())
        {
            throw std::runtime_error("Cannot create the new version of file!");
        }

        cryptography::ApplyXorCipherWithKey<>(
            std::istreambuf_iterator<char>(inputFile),
            std::istreambuf_iterator<char>(),
            std::ostreambuf_iterator<char>(outputFile),
            key
        );
    }
}

namespace fatpound::file
{
    auto NameAndExtension    (const std::filesystem::path& path) -> std::pair<std::string, std::string>
    {
        if (not std::filesystem::exists(path))
        {
            throw std::runtime_error("The given path to the file does NOT exist!");
        }

        if (not std::filesystem::is_regular_file(path))
        {
            throw std::runtime_error("The given path is NOT a regular file!");
        }

        return
        {
            path.stem().string(),
            path.extension().string()
        };
    }
    auto ToUriPath           (const std::filesystem::path& path) -> std::string
    {
        const auto& path_str = path.u8string();

        std::string uri;
        uri.reserve(path_str.length());

        for (const auto& ch : path_str)
        {
            if (static_cast<bool>(std::isalnum(ch)) or (ch == '-') or (ch == '_') or (ch == '.') or (ch == '~') or (ch == '/') or (ch == ':'))
            {
                uri.push_back(static_cast<char>(ch));
            }
            else if (ch == '\\')
            {
                uri.push_back('/');
            }
            else
            {
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4686)
#endif
                std::format_to<>(std::back_inserter<>(uri), "%{:02X}", static_cast<std::uint8_t>(ch));
#ifdef _MSC_VER
#pragma warning (pop)
#endif
            }
        }

        return uri;
    }
    auto LineCount_Unchecked (const std::filesystem::path& path) -> std::size_t
    {
        return CharCount_Unchecked<true>(path, '\n');
    }
    auto LineCount           (const std::filesystem::path& path) -> std::size_t
    {
        if (not std::filesystem::exists(path))
        {
            throw std::runtime_error("The given path does NOT exist!");
        }

        if (not std::filesystem::is_regular_file(path))
        {
            throw std::runtime_error("The given path is NOT a regular file!");
        }

        return LineCount_Unchecked(path);
    }
    auto LineCount_Dir       (const std::filesystem::path& path, const bool& recurse, const std::vector<std::string>& extensionFilter) -> std::size_t
    {
        return CharCount_Dir<true>(path, '\n', recurse, extensionFilter);
    }
    void PrintHex            (const std::filesystem::path& path, std::ostream& os)
    {
        std::ifstream file(path, std::ios::binary);

        if (not file.is_open())
        {
            throw std::runtime_error("Input file CANNOT be opened!");
        }

        {
            char first_byte{};

            if (file.get(first_byte))
            {
                os << std::format<>("{:02X}", static_cast<std::uint8_t>(first_byte));
            }
            else
            {
                return;
            }
        }

        std::vector<std::uint8_t> inbuf(8192U);
        std::string outbuf;
        outbuf.reserve(inbuf.size() * 3U);

        while (file.read(reinterpret_cast<char*>(inbuf.data()), static_cast<std::streamsize>(inbuf.size())))
        {
            for (std::size_t i{}; i < inbuf.size(); ++i)
            {
                std::format_to<>(std::back_inserter<>(outbuf), " {:02X}", inbuf[i]);
            }

            os << outbuf;
            outbuf.clear();
        }

        if (const auto& bytes_left = static_cast<std::size_t>(file.gcount()); bytes_left > 0U)
        {
            for (std::size_t i{}; i < bytes_left; ++i)
            {
                std::format_to<>(std::back_inserter<>(outbuf), " {:02X}", inbuf[i]);
            }

            os << outbuf;
        }
    }
    void EncryptDecrypt      (const std::filesystem::path& inPath, const std::size_t& key, std::filesystem::path outPath)
    {
        namespace fs = std::filesystem;

        const auto& outWasEmpty = outPath.parent_path().empty() or (inPath == outPath);

        if (outWasEmpty)
        {
            outPath = fs::temp_directory_path() / (inPath.stem().string() + "_temp.fat000");
        }
        else if (const auto& dirPath = outPath.parent_path(); not dirPath.empty())
        {
            std::filesystem::create_directories(dirPath);
        }

        details::EncryptDecrypt_Impl(inPath, key, outPath);

        if (outWasEmpty)
        {
            fs::remove(inPath);
            fs::rename(outPath, inPath);
        }
    }
    void EncryptDecrypt_Dir  (const std::filesystem::path& inPath, const std::size_t& key, std::filesystem::path outPath, const bool& recurse, const std::vector<std::string>& extensionFilter)
    {
        namespace fs = std::filesystem;

        if (not fs::is_directory(inPath))
        {
            throw std::runtime_error("Input path is NOT a directory!");
        }

        // NOLINTBEGIN(cppcoreguidelines-macro-usage)

        using DirIt = std::variant<fs::recursive_directory_iterator, fs::directory_iterator>;

        std::visit<>(
            [&inPath, &key, &outPath, &filters = extensionFilter](auto&& it) -> void
            {
#define FATLIB_FILE_ENCRYPTDECRYPT_DIR_LOOP_GENERATOR(...)                   \
                                                                             \
                for (const auto& dir_entry : it)                             \
                {                                                            \
                    if (fs::is_regular_file(dir_entry) __VA_ARGS__ )         \
                    {                                                        \
                        const auto& out_path = outPath.empty()               \
                            ?  outPath                                       \
                            : (outPath / fs::relative(dir_entry, inPath))    \
                            ;                                                \
                                                                             \
                        EncryptDecrypt(dir_entry, key, out_path);            \
                    }                                                        \
                }


                if (filters.empty())
                {
                    FATLIB_FILE_ENCRYPTDECRYPT_DIR_LOOP_GENERATOR()
                }
                else
                {
                    FATLIB_FILE_ENCRYPTDECRYPT_DIR_LOOP_GENERATOR(and (std::ranges::find(filters, dir_entry.path().extension().string()) not_eq filters.cend()))
                }

#undef FATLIB_FILE_ENCRYPTDECRYPT_DIR_LOOP_GENERATOR
            },
            recurse
                ? DirIt{ fs::recursive_directory_iterator{ inPath, fs::directory_options::skip_permission_denied } }
                : DirIt{ fs::directory_iterator          { inPath, fs::directory_options::skip_permission_denied } }
        );

        // NOLINTEND(cppcoreguidelines-macro-usage)
    }
}
