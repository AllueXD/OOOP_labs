#pragma once

#include "../src/BellmanFord.hpp"
#include "../src/Dijkstra.hpp"
#include "../src/Johnson.hpp"

namespace graph::algorithm {

    template<typename T>
    inline std::vector<int> BellmanFord(const Graph<T>& graph, int src) {
        impl::BellmanFordAlgorithm algo(graph, src);
        return algo.getResult();
    }

    template<typename T>
    inline std::vector<int> Dijkstra(const Graph<T>& graph, int src) {
        impl::DijkstraAlgorithm algo(graph, src);
        return algo.getResult();
    }

    template<typename T>
    inline std::vector<std::vector<int>> Johnson(const Graph <T> &graph) {
        impl::JohnsonAlgorithm<T> algo(graph);
        return algo.getResult();
    }
}
