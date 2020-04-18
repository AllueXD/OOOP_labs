#pragma once

#include "../include/Graph.hpp"

namespace graph::algorithm::impl::utilities {

    template<typename T>
    bool relax(std::vector<int> &distances, const typename Graph<T>::Edge &edge) {
        if (distances[edge.from] != INT_MAX && (distances[edge.to] == INT_MAX ||
                                                distances[edge.to] > distances[edge.from] + edge.weight)) {
            distances[edge.to] = distances[edge.from] + edge.weight;
            return true;
        }
        return false;
    }

    struct DijkstraVertices {
        int index = -1;
        int upperWeight = INT_MAX;

        DijkstraVertices() = default;

        explicit DijkstraVertices(int _index) : index(_index) {}

        DijkstraVertices(int _index, int weight) : index(_index), upperWeight(weight) {}
    };

    bool operator>(const DijkstraVertices &left, const DijkstraVertices &right) {
        return (left.upperWeight > right.upperWeight);
    }
}

namespace graph::algorithm::utilities {
    template<typename T>
    void printDistances(const Graph<T>& graph, const std::vector<int>& distances, int src) {
        std::vector<T> info = graph.getInfo();
        std::cout << "Shortest distances from vertex " << src << "(" << info[src] << ") to all another" << std::endl;
        for (int i = 0; i < distances.size(); i++) {
            std::cout << "Vertex: " << i << "(" << info[i] << "), distance: ";
            if (distances[i] == INT_MAX) {
                std::cout << "endless" << std::endl;
            } else {
                std::cout << distances[i] << std::endl;
            }
        }
    }
}
