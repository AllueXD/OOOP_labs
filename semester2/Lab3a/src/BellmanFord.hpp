#pragma once

#include <vector>
#include "../include/Graph.hpp"
#include "GraphUtils.hpp"

namespace graph::algorithm::impl {

    template<typename T>
    class BellmanFordAlgorithm {
        const Graph <T> &graph;
        int amountOfVertices;
        std::vector<int> distances;
        int src;

        bool hasNegativeCycle() {
            for (const auto &item : graph.getEdges()) {
                if (distances[item.from] != INT_MAX && distances[item.from] + item.weight < distances[item.to]) {
                    return true;
                }
            }
            return false;
        }

        void relaxAll() {
            for (int i = 0; i < amountOfVertices - 1; i++) {
                for (const auto &item : graph.getEdges()) {
                    utilities::relax<T>(distances, item);
                }
            }
        }

    public:
        BellmanFordAlgorithm(const Graph <T> &_graph, int _src) : graph(_graph), src(_src),
                amountOfVertices(_graph.getAmountOfVertices()), distances(amountOfVertices, INT_MAX)
        {
            distances[src] = 0;
            relaxAll();
            if (hasNegativeCycle()) {
                distances.clear();
            }
        }

        std::vector<int> getResult() {
            return distances;
        }
    };
}