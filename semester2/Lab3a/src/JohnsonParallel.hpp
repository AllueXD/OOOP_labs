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
            int firstPartEnd = (int)(amountOfVertices / 4);
            std::thread first([firstPartEnd, this]
                            {calculateDistancesInRange(0, firstPartEnd);});
            if (amountOfVertices > 1) {
                int secondPartEnd = (int)(amountOfVertices / 2);
                std::thread second([firstPartEnd, secondPartEnd, this]
                                   {calculateDistancesInRange(firstPartEnd + 1, secondPartEnd);});
                if (amountOfVertices > 2) {
                    int thirdPartEnd = (int)(3 * amountOfVertices / 4);
                    std::thread third([thirdPartEnd, secondPartEnd, this]
                                      {calculateDistancesInRange(secondPartEnd + 1, thirdPartEnd);});
                    if (amountOfVertices > 3) {
                        int fourthPartEnd = amountOfVertices - 1;
                        std::thread fourth([thirdPartEnd, fourthPartEnd, this]
                        {calculateDistancesInRange(thirdPartEnd + 1, fourthPartEnd);});
                        first.join();
                        second.join();
                        third.join();
                        fourth.join();
                    } else {
                        first.join();
                        second.join();
                        third.join();
                    }
                } else {
                    first.join();
                    second.join();
                }
            } else {
                first.join();
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