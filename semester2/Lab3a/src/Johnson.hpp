#pragma once

#include "../include/Graph.hpp"
#include "BellmanFord.hpp"
#include "Dijkstra.hpp"
#include "JohnsonBase.hpp"

namespace graph::algorithm::impl {

    template<typename T>
    class JohnsonAlgorithm : public JohnsonBase<T> {
    private:
        using JohnsonBase<T>::amountOfVertices;
        using JohnsonBase<T>::distances;
        using JohnsonBase<T>::graph;
        using JohnsonBase<T>::checkBellmanFord;
        using JohnsonBase<T>::updateNegativeEdges;

        void calculateDistancesForEachVertex() override {
            for (int i = 0; i < amountOfVertices; i++) {
                DijkstraAlgorithm algo(graph, i);
                distances.push_back(algo.getResult());
            }
        }

    public:
        using JohnsonBase<T>::getResult;
        JohnsonAlgorithm(const Graph <T>& _graph) : JohnsonBase<T>(_graph) {
            if (checkBellmanFord()) {
                updateNegativeEdges();
                distances.reserve(amountOfVertices);
                calculateDistancesForEachVertex();
            }
        }
    };
}
