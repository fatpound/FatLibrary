#pragma once

#include <DSA/include/DirectedGraph.hpp>

#include <string>

namespace fatpound::algorithm
{
    /// @brief Performs a breadth-first search (BFS) traversal on a directed graph starting from node 0 and returns the traversal order as a string
    /// 
    /// @param graph: The directed graph to traverse
    /// 
    /// @return A string representing the order in which nodes are visited during BFS, with each node encoded as a lowercase letter starting from 'a'
    /// 
    auto BFS(const dsa::DirectedGraph& graph) -> std::string;
}
