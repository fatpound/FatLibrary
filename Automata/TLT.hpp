#pragma once

#include <Automata/CFG.hpp>

#include <cstddef>

#include <iostream>
#include <vector>
#include <string>

namespace fatpound::automata
{
    class TLT final
    {
        static constexpr auto scx_recurse_limit_ = 1U;

    public:
        explicit TLT(const CFG& cfg);
        explicit TLT(const std::string& inputFilename);

        explicit TLT()               = delete;
        explicit TLT(const TLT&)     = delete;
        explicit TLT(TLT&&) noexcept = delete;

        auto operator = (const TLT&)     -> TLT& = delete;
        auto operator = (TLT&&) noexcept -> TLT& = delete;
        ~TLT() noexcept(false);


    public:
        [[nodiscard]] auto GetWords() const -> std::vector<std::string>;

        void PrintWords(std::ostream& os = std::cout) const;


    protected:


    private:
        // NOLINTBEGIN(altera-struct-pack-align)
        struct alignas(64) Node_ final
        {
            explicit Node_(std::string item) noexcept;

            std::vector<Node_*>   m_leaves;
            std::string           m_item;
        };
        // NOLINTEND(altera-struct-pack-align)


    private:
        static auto IsTerminal_(const std::string& word) noexcept -> bool;


    private:
        void CreateTree_     (Node_* const node);
        void CreateInnerTree_(Node_* const node);

        void Clear_();


    private:
        const CFG::Grammar_t       mc_cfgrammar_;

        std::vector<std::string>   m_results_;
        std::vector<std::size_t>   m_recursers_;

        Node_*                     m_pTree_{};
    };
}
