#include "TLT.hpp"

#include <cctype>

#include <utility>
#include <algorithm>
#include <deque>
#include <stdexcept>

namespace fatpound::automata
{
    // TLT

    TLT::TLT(const CFG& cfg)
        :
        mc_cfgrammar_(cfg.GetGrammar()),
        m_recursers_(mc_cfgrammar_.size(), 0)
    {
        if (mc_cfgrammar_.empty())
        {
            throw std::runtime_error("There is no input!");
        }

        m_pTree_ = new Node_(mc_cfgrammar_[0].first);

        for (const auto& leaf_str : mc_cfgrammar_[0].second)
        {
            m_pTree_->m_leaves.push_back(new Node_(leaf_str));
        }

        CreateTree_(m_pTree_);
    }
    TLT::TLT(const std::string& inputFilename)
        :
        TLT(CFG{ inputFilename })
    {

    }
    TLT::~TLT() noexcept(false)
    {
        Clear_();
    }


    auto TLT::GetWords() const -> std::vector<std::string>
    {
        return m_results_;
    }

    void TLT::PrintWords(std::ostream& os) const
    {
        std::vector<std::string> finals;
        std::vector<std::string> repeaters;

        for (const auto& str : m_results_)
        {
            if (std::ranges::find(finals, str) == finals.cend())
            {
                finals.push_back(str);
            }
            else if (std::ranges::find(repeaters, str) == repeaters.cend())
            {
                repeaters.push_back(str);
            }
        }

        if (not finals.empty())
        {
            for (const auto& str : finals)
            {
                os << str << '\n';
            }
        }

        if (not repeaters.empty())
        {
            os << "\nRepeaters :\n\n";

            for (const auto& str : repeaters)
            {
                os << str << '\n';
            }
        }

        os << '\n';
    }

    auto TLT::IsTerminal_(const std::string& word) noexcept -> bool
    {
        return std::ranges::all_of(word, [](const auto& ch) noexcept -> bool { return std::islower(ch) not_eq 0; });
    }

    void TLT::CreateTree_      (Node_* const node)
    {
        m_results_.reserve(node->m_leaves.size());

        for (auto& leaf : node->m_leaves)
        {
            if (IsTerminal_(leaf->m_item))
            {
                m_results_.push_back(leaf->m_item);

                continue;
            }

            CreateInnerTree_(leaf);
        }
    }
    void TLT::CreateInnerTree_ (Node_* const node)
    {
        for (std::size_t i{}; i < node->m_item.size(); ++i)
        {
            const auto ch = node->m_item[i];

            if (std::isupper(ch) == 0)
            {
                continue;
            }

            const auto& cfg_it = std::ranges::find_if(mc_cfgrammar_, [ch](const auto& pair) { return pair.first[0] == ch; });

            const std::string leftstr(node->m_item.cbegin(), node->m_item.cbegin() + static_cast<std::ptrdiff_t>(i));
            const std::string rightstr(node->m_item.cbegin() + static_cast<std::ptrdiff_t>(i + 1U), node->m_item.cend());

            const auto index = static_cast<std::size_t>(cfg_it - mc_cfgrammar_.cbegin());

            node->m_leaves.reserve(node->m_leaves.size() + cfg_it->second.size());

            for (const auto& cfgstr : cfg_it->second)
            {
                // string str = cfgstr;

                bool recursed{};

#if __cplusplus >= 202302L
                if (cfgstr.contains(ch))
#else
                if (cfgstr.find(ch) not_eq std::string::npos)
#endif
                {
                    if (m_recursers_[index] >= scx_recurse_limit_)
                    {
                        continue;
                    }

                    recursed = true;

                    ++m_recursers_[index];
                }

                {
                    std::string newstr = leftstr;

                    newstr += cfgstr;
                    newstr += rightstr;

                    auto* newnode = new Node_(newstr);

                    node->m_leaves.push_back(newnode);

                    if (recursed or (not IsTerminal_(newstr)))
                    {
                        CreateInnerTree_(newnode);
                    }
                    else
                    {
                        m_results_.push_back(newstr);
                    }
                }

                if (recursed)
                {
                    --m_recursers_[index];
                }
            }
        }
    }
    void TLT::Clear_()
    {
        if (m_pTree_ == nullptr)
        {
            return;
        }

        std::deque<Node_*> nodes;

        nodes.push_back(m_pTree_);

        while (not nodes.empty())
        {
            Node_* const node = nodes.back();

            nodes.pop_back();

            for (auto& leaf : node->m_leaves)
            {
                nodes.push_back(leaf);
            }

            delete node;
        }
    }


    // TLT::Node_

    TLT::Node_::Node_(std::string item) noexcept
        :
        m_item(std::move<>(item))
    {

    }
}
