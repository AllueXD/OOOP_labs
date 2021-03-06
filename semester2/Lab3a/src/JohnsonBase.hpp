#pragma once

#include "../include/Graph.hpp"
#include "BellmanFord.hpp"

namespace graph::algorithm::impl {

    template<typename T>
    class JohnsonBase {
    protected:
        Graph <T> graph;
        int amountOfVertices;
        std::vector<std::vector<int>> distances;
        std::vector<int> distancesForModified;

        void modifyGraph() {
            graph.addVertex(T());
            for (int i = 0; i < amountOfVertices; i++) {
                graph.addEdge(amountOfVertices, i, 0);
            }
        }

        bool checkBellmanFord() {
            BellmanFordAlgorithm algo(graph, amountOfVertices);
            distancesForModified = algo.getResult();
            return (!distancesForModified.empty());
        }

        void updateNegativeEdges() {
            graph.eraseVertex(amountOfVertices);
            for (const auto &item : graph.getEdges()) {
                graph.changeEdgeWeight(item.from, item.to,
                                       item.weight + distancesForModified[item.from] - distancesForModified[item.to]);
            }
        }

        virtual void calculateDistancesForEachVertex() = 0;

    public:
        explicit JohnsonBase(const Graph <T> &_graph) : graph(_graph),
                                                             amountOfVertices(_graph.getAmountOfVertices())
        {
            modifyGraph();
        }

        std::vector<std::vector<int>> getResult() {
            return distances;
        }
    };
}
