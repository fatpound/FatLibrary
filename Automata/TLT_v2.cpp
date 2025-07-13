#include <Automata/TLT_v2.hpp>

#include <cctype>

#include <deque>
#include <algorithm>
#include <stdexcept>

namespace fatpound::automata
{
    // TLT_v2

    TLT_v2::TLT_v2(const CFG& cfg)
    {
        {
            const auto& cfgrammar = cfg.GetGrammar();

            m_trees_.reserve(cfgrammar.size());

            for (const auto& tree : cfgrammar)
            {
                m_trees_.push_back(new Node_(tree));
            }
        }

        m_results_ = GenerateResults_("", 0U, 0U);
    }
    TLT_v2::TLT_v2(const std::string& inputFilename)
        :
        TLT_v2(CFG{ inputFilename })
    {

    }
    TLT_v2::~TLT_v2() noexcept(false)
    {
        Clear_();
    }


    auto TLT_v2::GetWords() const -> Result_t
    {
        return m_results_;
    }
    void TLT_v2::PrintWords(std::ostream& os) const
    {
        for (const auto& item : m_results_)
        {
            if (item.second)
            {
                os << item.first << '\n';
            }
        }
    }

    auto TLT_v2::GenerateResults_(const std::string& init_str, const std::size_t& index, const std::size_t& recursed) const -> Result_t
    {
        Result_t strings;

        for (const auto& node : m_trees_[index]->m_leaves)
        {
            Result_t tempstrings{ { init_str, false } };

            for (const auto ch : node->m_item)
            {
                Result_t newTempStrings;

                for (const auto& strPair : tempstrings)
                {
                    std::string& str = newTempStrings.emplace_back(strPair).first;

                    const auto insertedindex = newTempStrings.size() - 1;

                    const auto it = std::find_if<>(m_trees_.cbegin() + static_cast<std::ptrdiff_t>(index), m_trees_.cend(), [ch](const auto& tree) -> bool { return ch == tree->m_item[0]; });

                    if (it == m_trees_.cend() or recursed >= scx_RecursionLimit_)
                    {
                        str += ch;

                        continue;
                    }

                    {
                        const auto tree_index = static_cast<std::size_t>(it - m_trees_.cbegin());
                        const auto will_recurse = static_cast<std::size_t>(tree_index == index);

                        if (strPair.first.empty())
                        {
                            continue;
                        }

                        const auto vec = GenerateResults_(strPair.first, tree_index, recursed + will_recurse);

                        for (const auto& pair : vec)
                        {
                            newTempStrings.emplace_back(pair);
                        }
                    }

                    newTempStrings.erase(newTempStrings.begin() + static_cast<std::ptrdiff_t>(insertedindex));
                }

                tempstrings = std::move<>(newTempStrings);
            }

            for (const auto& strPair : tempstrings)
            {
                strings.emplace_back(strPair.first, IsTerminal_(strPair.first));
            }
        }

        return strings;
    }
    auto TLT_v2::IsTerminal_(const std::string& str) const -> bool
    {
        for (const auto& tree : m_trees_)
        {
            if (std::ranges::any_of(str, [&tree](const auto& ch) -> bool { return ch == (tree->m_item[0]); }))
            {
                return false;
            }
        }

        return true;
    }
    void TLT_v2::Clear_()
    {
        std::deque<Node_*> nodes;

        for (auto& tree : m_trees_)
        {
            if (tree not_eq nullptr)
            {
                nodes.push_back(tree);
            }
            else
            {
                continue;
            }

            while (not nodes.empty())
            {
                Node_* node = nodes.back();

                nodes.pop_back();

                for (auto& leaf : node->m_leaves)
                {
                    nodes.push_back(leaf);
                }

                delete node;
            }
        }
    }


    // TLT_v2::Node_

    TLT_v2::Node_::Node_(const std::pair<std::string, std::vector<std::string>>& tree)
        :
        m_item(tree.first)
    {
        m_leaves.reserve(tree.second.size());

        for (const auto& str : tree.second)
        {
            m_leaves.push_back(new Node_(str));
        }
    }
    TLT_v2::Node_::Node_(std::string item) noexcept
        :
        m_item(std::move<>(item))
    {

    }
}
