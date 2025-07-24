#include "BFS.hpp"

#include <Colors/ARGB/ARGB.hpp>

#include <cstddef>

#include <vector>
#include <queue>

namespace fatpound::graph
{
    auto BFS(const DirectedGraph& graph) -> std::string
    {
        std::vector<colors::argb::Color> colors(graph.GetNodeCount());

        std::queue<std::size_t> queue;
        queue.push(0);

        std::string output;

        while (not queue.empty())
        {
            const auto& u = queue.front();
            queue.pop();

            for (std::size_t i{}; i < graph.GetNextCount(u); ++i)
            {
                if (const auto& v = graph.GetNextAt(u, i); colors[v] == colors::argb::White)
                {
                    colors[v] = colors::argb::Gray;
                    queue.push(v);
                }
            }

            colors[u] = colors::argb::Black;

            output += static_cast<char>('a' + u);
        }

        return output;
    }
}
