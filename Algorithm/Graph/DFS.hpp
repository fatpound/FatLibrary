#pragma once

#include <DSA/DirectedGraph.hpp>
#include <Utility/Color.hpp>

#include <cstddef>

#include <vector>
#include <string>
#include <format>

namespace fatpound::algorithm::details
{
    static auto DFS_Visit_(const dsa::DirectedGraph& graph, std::vector<utility::Color>& colors, const std::size_t& index) -> std::string
    {
        colors[index] = colors::Gray;

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4686)
#endif
        std::string output = std::format<>("{}\n", index);
#ifdef _MSC_VER
#pragma warning (pop)
#endif

        for (std::size_t i{}; i < graph.GetNextCount(index); ++i)
        {
            if (const auto& nextIndex = graph.GetNextAt(index, i); colors[nextIndex] == colors::White)
            {
                output += DFS_Visit_(graph, colors, nextIndex);
            }
        }

        colors[index] = colors::Black;

        return output;
    }
}

namespace fatpound::algorithm
{
    static auto DFS(const dsa::DirectedGraph& graph) -> std::string
    {
        std::string output;

        std::vector<utility::Color> colors(graph.GetNodeCount());

        for (std::size_t i{}; i < graph.GetNodeCount(); ++i)
        {
            if (colors[i] == colors::White)
            {
                output += details::DFS_Visit_(graph, colors, i);
            }
        }

        return output;
    }
}
