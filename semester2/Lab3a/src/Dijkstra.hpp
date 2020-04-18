#pragma once

#include "../include/Graph.hpp"
#include "GraphUtils.hpp"
#include <queue>

namespace graph::algorithm::impl {

    template<typename T>
    class DijkstraAlgorithm {

    private:
        const Graph<T> &graph;
        int src;
        int amountOfVertices;
        std::vector<int> distances;
        std::priority_queue<utilities::DijkstraVertices,
            std::vector<utilities::DijkstraVertices>, std::greater<>> queue;
        int currIndex;

        void fillQueue() {
            for (int i = 0; i < src; i++) {
                queue.emplace(utilities::DijkstraVertices(i));
            }
            queue.emplace(utilities::DijkstraVertices(src, 0));
            for (int i = src + 1; i < amountOfVertices; i++) {
                queue.emplace(utilities::DijkstraVertices(i));
            }
        }

        void relaxConnected() {
            for (const auto &item : graph.getEdges()) {
                if (item.from == currIndex) {
                    if (utilities::relax<T>(distances, item)) {
                        queue.emplace(utilities::DijkstraVertices(item.to, distances[item.to]));
                    }
                }
            }
        }

        void freeQueue() {
            while (!queue.empty()) {
                utilities::DijkstraVertices currVertex = queue.top();
                currIndex = currVertex.index;
                queue.pop();
                if (currVertex.upperWeight != distances[currIndex]) {
                    continue;
                }

                relaxConnected();
            }
        }

    public:
        DijkstraAlgorithm(const Graph<T>& _graph, int _src) : graph(_graph), src(_src),
                amountOfVertices(_graph.getAmountOfVertices()), distances(amountOfVertices, INT_MAX)
        {
            distances[src] = 0;

            fillQueue();
            freeQueue();
        }

        std::vector<int> getResult() {
            return distances;
        }
    };



//    bool operator==(const DijkstraVertices &left, const DijkstraVertices &right) {
//        return (left.index == right.index);
//    }
//
//    bool operator!=(const DijkstraVertices &left, const DijkstraVertices &right) {
//        return (left.index != right.index);
//    }
//
//    bool operator<(const DijkstraVertices &left, const DijkstraVertices &right) {
//        return (left.upperWeight < right.upperWeight);
//    }

}

