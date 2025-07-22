#include "DirectedGraph.hpp"

#include <Utility/include/Common.hpp>

#include <ios>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace fatpound::graph
{
    DirectedGraph::DirectedGraph(const std::string& path)
    {
        {
            std::ifstream file(path, std::ios_base::binary);

            if (not file.is_open())
            {
                throw std::runtime_error("Input file cannot be opened!");
            }

            std::string line;

            while (std::getline<>(file, line))
            {
                if (line.empty())
                {
                    throw std::runtime_error("Line is EMPTY!");
                }

                m_adj_.emplace_back(utility::ParseLineToIntegralVector<typename decltype(m_adj_)::value_type::value_type>(line));
            }
        }

        if (m_adj_.empty())
        {
            throw std::runtime_error("Input graph was EMPTY!");
        }

        m_node_count_ = m_adj_.size();

        m_nexts_.resize(m_node_count_);

        for (std::size_t i{}; i < m_node_count_; ++i)
        {
            for (std::size_t j{}; j < m_node_count_; ++j)
            {
                if (m_adj_[i][j] not_eq 0)
                {
                    m_nexts_[i].push_back(j);

                    ++m_edge_count_;
                }
            }
        }
    }


    auto DirectedGraph::GetAdjAt (const std::size_t& u, const std::size_t& v) const noexcept -> std::ptrdiff_t
    {
        return m_adj_[u][v];
    }
    auto DirectedGraph::GetNextAt(const std::size_t& u, const std::size_t& v) const noexcept -> std::size_t
    {
        return m_nexts_[u][v];
    }

    auto DirectedGraph::GetNextCount(const std::size_t& idx) const noexcept -> std::size_t
    {
        return m_nexts_[idx].size();
    }

    auto DirectedGraph::GetNodeCount() const noexcept -> std::size_t
    {
        return m_node_count_;
    }
    auto DirectedGraph::GetEdgeCount() const noexcept -> std::size_t
    {
        return m_edge_count_;
    }
}
