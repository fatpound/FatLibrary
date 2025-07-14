#pragma once

#include "CFG.hpp"

#include <cstddef>

#include <iostream>
#include <vector>
#include <string>
#include <utility>

namespace fatpound::automata
{
    class TLT_v2 final
    {
        static constexpr auto scx_RecursionLimit_ = 1U;

    public:
        using Result_t = std::vector<std::pair<std::string, bool>>;


    public:
        explicit TLT_v2(const CFG& cfg);
        explicit TLT_v2(const std::string& inputFilename);

        explicit TLT_v2()               = delete;
        explicit TLT_v2(const TLT_v2&)     = delete;
        explicit TLT_v2(TLT_v2&&) noexcept = delete;

        auto operator = (const TLT_v2&)     -> TLT_v2& = delete;
        auto operator = (TLT_v2&&) noexcept -> TLT_v2& = delete;
        ~TLT_v2() noexcept(false);


    public:
        [[nodiscard]] auto GetWords() const -> Result_t;

        void PrintWords(std::ostream& os = std::cout) const;


    protected:


    private:
        // NOLINTBEGIN(altera-struct-pack-align)
        struct alignas(64) Node_ final
        {
            explicit Node_(const std::pair<std::string, std::vector<std::string>>& tree);
            explicit Node_(std::string item) noexcept;

            std::vector<Node_*>   m_leaves;
            std::string           m_item;
        };
        // NOLINTEND(altera-struct-pack-align)


    private:
        // NOLINTBEGIN(readability-function-cognitive-complexity)
        [[nodiscard]] auto GenerateResults_(const std::string& init_str = "", const std::size_t& index = {}, const std::size_t& recursed = {}) const -> Result_t;
        // NOLINTEND(readability-function-cognitive-complexity)

        [[nodiscard]] auto IsTerminal_(const std::string& str) const -> bool;

        void Clear_();


    private:
        Result_t              m_results_;
        std::vector<Node_*>   m_trees_;
    };
}
