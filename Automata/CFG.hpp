#pragma once

#include <cctype>

#include <fstream>
#include <vector>
#include <string>
#include <utility>

namespace fatpound::automata
{
    class CFG final
    {
        static constexpr auto scx_SymbolDelimiter_          = '|';
        static constexpr auto scx_LanguageDelimiter_        = ',';
        static constexpr auto scx_LanguageContentIndicator_ = "-->";

    public:
        using LanguageName_t = std::string;
        using       Symbol_t = std::string;
        using     Alphabet_t = std::vector<char>;
        using     Language_t = std::pair<LanguageName_t, std::vector<Symbol_t>>;
        using      Grammar_t = std::vector<Language_t>;


    public:
        // The input file should be in the following format:
        //
        // 1st line: The alphabet, the languages' acceptable letters separated by spaces (they must be common)
        // 2nd line: The languages are separated by commas and are defined by their names followed by an arrow which is like this "-->"
        // and followed by the symbols of the language(terminals and non - terminals) separated by a pipe character '|'
        // The separators can be changed. See static constexpr variables below
        //
        // Example:
        // a b  c   d e
        // S --> aa | bX | aXX, X --> ab | b
        //
        explicit CFG(const std::string& inputFilename);

        explicit CFG()               = delete;
        explicit CFG(const CFG&)     = delete;
        explicit CFG(CFG&&) noexcept = delete;

        auto operator = (const CFG&)     -> CFG& = delete;
        auto operator = (CFG&&) noexcept -> CFG& = delete;
        ~CFG() noexcept                          = default;


    public:
        [[nodiscard]]
        auto GetGrammar() const -> Grammar_t;


    protected:


    private:
        static void ReadFirstLine_(std::ifstream& inputFile, Alphabet_t& alphabet);


    private:
        void ReadSecondLine_(std::ifstream& inputFile, const Alphabet_t& alphabet);


    private:
        Grammar_t m_grammar_;
    };
}
