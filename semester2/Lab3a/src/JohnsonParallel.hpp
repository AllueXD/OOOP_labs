#pragma once

#include "../include/Graph.hpp"
#include "JohnsonBase.hpp"
#include "Dijkstra.hpp"
#include <thread>
#include <cmath>

namespace graph::algorithm::impl {

    template<typename T>
    class JohnsonParallel : public JohnsonBase<T> {
    private:
        using JohnsonBase<T>::amountOfVertices;
        using JohnsonBase<T>::distances;
        using JohnsonBase<T>::graph;
        using JohnsonBase<T>::checkBellmanFord;
        using JohnsonBase<T>::updateNegativeEdges;

        void calculateDistancesInRange(int start, int end) {
            for (int i = start; i <= end && i < amountOfVertices; i++) {
                DijkstraAlgorithm algo(graph, i);
                distances[i] = algo.getResult();
            }
        }

        void calculateDistancesForEachVertex() override {
            distances.resize(amountOfVertices);
            int HW_concurrency = std::thread::hardware_concurrency();
            std::vector<std::thread> threads(HW_concurrency);
            int start = 0, end = -1;
            for (int i = 0; i < HW_concurrency; i++) {
                start = end + 1;
                end = (int)((i + 1) * amountOfVertices / 4);
                threads[i] = std::thread([start, end, this]
                                         {calculateDistancesInRange(start, end);});
            }

            for (auto& th : threads) {
                th.join();
            }
        }

    public:
        using JohnsonBase<T>::getResult;
        JohnsonParallel(const Graph <T>& _graph) : JohnsonBase<T>(_graph) {
            if (checkBellmanFord()) {
                updateNegativeEdges();
                distances.reserve(amountOfVertices);
                calculateDistancesForEachVertex();
            }
        }
    };
}