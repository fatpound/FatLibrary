#include "TLT_v2.hpp"

#include <iostream>
#include <deque>
#include <algorithm>

namespace fatpound::automata
{
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

        m_results_ = GenerateResults_("", 0u, 0u);
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

    auto TLT_v2::GetWords() const noexcept -> Result_t
    {
        return m_results_;
    }

    void TLT_v2::PrintWords() const
    {
        for (const auto& item : m_results_)
        {
            if (item.second == true)
            {
                std::cout << item.first << '\n';
            }
        }
    }

    auto TLT_v2::GenerateResults_(std::string init_str, std::size_t index, std::size_t recursed) const -> Result_t
    {
        Result_t strings;

        for (const auto& node : m_trees_[index]->m_leaves)
        {
            Result_t tempstrings;

            tempstrings.emplace_back(init_str, false);

            for (const auto& ch : node->m_item)
            {
                Result_t newTempStrings;

                for (const auto& strPair : tempstrings)
                {
                    std::string& str = newTempStrings.emplace_back(strPair).first;

                    const auto insertedindex = newTempStrings.size() - 1;

                    const auto it = std::find_if(m_trees_.cbegin() + static_cast<std::ptrdiff_t>(index), m_trees_.cend(), [&](const auto& tree) -> bool { return ch == tree->m_item[0]; });

                    if (it == m_trees_.cend())
                    {
                        str += ch;
                    }
                    else
                    {
                        const auto tree_index = static_cast<std::size_t>(it - m_trees_.cbegin());
                        const auto will_recurse = static_cast<::std::size_t>((tree_index == index) ? 1 : 0);

                        if (recursed < scx_RecursionLimit_)
                        {
                            // const auto size = tempstrings.size();

                            // bool deleted = false;

                            std::string tempstr = strPair.first;

                            if (tempstr.empty())
                            {
                                continue;
                            }

                            const auto vec = GenerateResults_(tempstr, tree_index, recursed + will_recurse);

                            for (const auto& pair : vec)
                            {
                                newTempStrings.emplace_back(pair);
                            }

                            newTempStrings.erase(newTempStrings.begin() + static_cast<std::ptrdiff_t>(insertedindex));
                        }
                        else
                        {
                            str += ch;
                        }
                    }
                }

                tempstrings = std::move(newTempStrings);
            }

            for (const auto& strPair : tempstrings)
            {
                strings.emplace_back(strPair.first, IsTerminal_(strPair.first));
            }
        }

        return strings;
    }

    bool TLT_v2::IsTerminal_(const std::string& str) const
    {
        for (const auto& tree : m_trees_)
        {
            if (std::any_of(str.cbegin(), str.cend(), [&](const auto& ch) -> bool { return ch == (tree->m_item[0]); }))
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

            while (nodes.size() > 0)
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
    TLT_v2::Node_::Node_(const std::string& str)
        :
        m_item(str)
    {

    }
}