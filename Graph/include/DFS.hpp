#pragma once

#include <Graph/include/DirectedGraph.hpp>

#include <string>

namespace fatpound::graph
{
    /// @brief Performs a depth-first search (DFS) traversal on a directed graph and returns the traversal order as a string
    /// 
    /// @param graph: The directed graph to traverse
    /// 
    /// @return A string representing the order in which the nodes are visited during the DFS traversal
    /// 
    auto DFS(const DirectedGraph& graph) -> std::string;
}
