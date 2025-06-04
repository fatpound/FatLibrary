#pragma once

#include <DSA/DirectedGraph.hpp>
#include <Utility/Color.hpp>

#include <cstddef>

#include <vector>
#include <string>
#include <queue>

namespace fatpound::algorithm
{
    /// @brief Performs a breadth-first search (BFS) traversal on a directed graph starting from node 0 and returns the traversal order as a string
    /// 
    /// @param graph: The directed graph to traverse
    /// 
    /// @return A string representing the order in which nodes are visited during BFS, with each node encoded as a lowercase letter starting from 'a'
    /// 
    static auto BFS(const dsa::DirectedGraph& graph) -> std::string
    {
        std::vector<utility::Color> colors(graph.GetNodeCount());

        std::queue<std::size_t> queue;
        queue.push(0);

        std::string output;

        while (not queue.empty())
        {
            const auto& u = queue.front();
            queue.pop();

            for (std::size_t i{}; i < graph.GetNextCount(u); ++i)
            {
                if (const auto& v = graph.GetNextAt(u, i); colors[v] == colors::White)
                {
                    colors[v] = colors::Gray;
                    queue.push(v);
                }
            }

            colors[u] = colors::Black;

            output += static_cast<char>('a' + u);
        }

        return output;
    }
}
