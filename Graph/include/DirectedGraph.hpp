#pragma once

#include <cstddef>

#include <vector>
#include <string>

namespace fatpound::graph
{
    class DirectedGraph
    {
    public:
        explicit DirectedGraph(const std::string& path);
        
        explicit DirectedGraph()                         = delete;
        explicit DirectedGraph(const DirectedGraph&)     = delete;
        explicit DirectedGraph(DirectedGraph&&) noexcept = delete;

        auto operator = (const DirectedGraph&)     -> DirectedGraph& = delete;
        auto operator = (DirectedGraph&&) noexcept -> DirectedGraph& = delete;
        ~DirectedGraph() noexcept                                    = default;


    public:
        [[nodiscard]] auto GetAdjAt (const std::size_t& u, const std::size_t& v) const noexcept -> std::ptrdiff_t;
        [[nodiscard]] auto GetNextAt(const std::size_t& u, const std::size_t& v) const noexcept -> std::size_t;

        [[nodiscard]] auto GetNextCount(const std::size_t& idx) const noexcept -> std::size_t;

        [[nodiscard]] auto GetNodeCount() const noexcept -> std::size_t;
        [[nodiscard]] auto GetEdgeCount() const noexcept -> std::size_t;


    protected:


    private:
        std::vector<std::vector<std::ptrdiff_t>>   m_adj_;
        std::vector<std::vector<std::size_t>>      m_nexts_;

        std::size_t                                m_node_count_{};
        std::size_t                                m_edge_count_{};
    };
}