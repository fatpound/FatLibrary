#include "CFG.hpp"

#include <cctype>

#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <string_view>
#include <ranges>

namespace fatpound::automata
{
    CFG::CFG(const std::string& inputFilename)
    {
        std::ifstream inputFile(inputFilename);

        if (not inputFile.is_open())
        {
            throw std::runtime_error("Input file cannot be opened for [InputtingCFG]!");
        }

        Alphabet_t alphabet;

        S_ReadLine1_(inputFile, alphabet);
        S_ReadLine2_(inputFile, alphabet, m_grammar_);
    }


    auto CFG::GetGrammar() const -> Grammar_t
    {
        return m_grammar_;
    }

    auto CFG::S_GenerateLanguageSymbols_(const Symbol_t& symbol, const Alphabet_t& alphabet) -> std::vector<Symbol_t>
    {
        std::vector<Symbol_t> symbols;

        std::istringstream iss(symbol);

        std::string tempstr;

        while (std::getline<>(iss, tempstr, scx_SymbolDelimiter_))
        {
            if (std::ranges::find(symbols, tempstr) not_eq symbols.cend())
            {
                continue;
            }

            for (const auto& ch : tempstr)
            {
                if ((std::islower(ch) not_eq 0)
                    and
                    std::ranges::find(alphabet, ch) == alphabet.cend())
                {
                    throw std::runtime_error("The letter " + std::string{ ch } + " is not in the alphabet!");
                }
            }

            symbols.push_back(tempstr);
        }

        return symbols;
    }

    auto CFG::S_GetLanguageName_(const std::string& linestr) -> std::string
    {
        return { linestr.cbegin(), linestr.cbegin() + static_cast<std::ptrdiff_t>(S_GetLanguageCIIdx_(linestr)) };
    }
    auto CFG::S_GetLanguageCIIdx_(const std::string& linestr) -> std::size_t
    {
        const auto idx = linestr.find(scx_LanguageContentIndicator_);

        if (idx not_eq std::string::npos)
        {
            return idx;
        }

        throw std::runtime_error("Cannot find language content indicator in line!");
    }

    void CFG::S_ReadLine1_(std::ifstream& inputFile, Alphabet_t& alphabet)
    {
        {
            std::stringstream ss;

            {
                std::string str;
                std::getline<>(inputFile, str);

                ss << str;
            }

            char ch{};

            while (ss >> ch)
            {
                alphabet.push_back(ch);
            }
        }

        std::ranges::sort(alphabet);

        const auto& [beg, end] = std::ranges::unique(alphabet);
        alphabet.erase(beg, end);
    }
    void CFG::S_ReadLine2_(std::ifstream& inputFile, const Alphabet_t& alphabet, Grammar_t& grammar)
    {
        std::string str;

        while (std::getline<>(inputFile, str, scx_LanguageDelimiter_))
        {
            {
                const auto& [beg, end] = std::ranges::remove_if(str, [](const auto& ch) noexcept -> bool { return std::isspace(ch) not_eq 0; });
                str.erase(beg, end);
            }

            grammar.emplace_back(
                S_GetLanguageName_(str),
                S_GenerateLanguageSymbols_(str.substr(S_GetLanguageCIIdx_(str) + std::string_view{ scx_LanguageContentIndicator_ }.size()), alphabet)
            );
        }
    }
}
