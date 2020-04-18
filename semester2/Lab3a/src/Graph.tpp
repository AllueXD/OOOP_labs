#pragma once

#include <vector>
#include <cassert>
#include "../include/Graph.hpp"


namespace graph {

    template <typename T>
    int Graph<T>::getEdgeIndex(int first, int second) {
        for (int i = 0; i < edges.size(); i++) {
            if (edges[i].from == first && edges[i].to == second) {
                return i;
            }
        }
        return -1;
    }

    template <typename T>
    void Graph<T>::changeEdgeWeight(int index, int weight) {
        assert(index >= 0 && index < edges.size());
        edges[index].weight = weight;
    }

    template <typename T>
    Graph<T>::Graph(const std::vector<T> &_info)
            : amountOfVertices(_info.size()) {
        for (auto item : _info) {
            info.push_back(item);
        }
    }

    template <typename T>
    Graph<T>::Graph(const Graph &graph) {
        amountOfVertices = graph.getAmountOfVertices();
        amountOfEdges = graph.getAmountOfEdges();
        for (auto item : graph.getInfo()) {
            info.push_back(item);
        }
        amountOfVertices = info.size();

        for (auto item : graph.edges) {
            edges.push_back(Edge(item.from, item.to, item.weight));
        }
    }

    template <typename T>
    void Graph<T>::addVertex(const T &vertInfo) {
        info.push_back(vertInfo);
        amountOfVertices++;
    }

    template <typename T>
    void Graph<T>::eraseVertex(int index) {
        info.erase(info.begin() + index);
        amountOfVertices--;
        auto it = edges.begin();
        while (it != edges.end()) {
            if ((*it).from == index || (*it).to == index) {
                it = edges.erase(it);
                amountOfEdges--;
            } else {
                it++;
            }
        }
    }

    template <typename T>
    void Graph<T>::addEdge(int first, int second) {
        assert(first < amountOfVertices && second < amountOfVertices);
        if (changeEdgeWeight(first, second, info[first] - info[second])) {
            return;
        }
        edges.push_back(Edge(first, second, info[first] - info[second]));
        amountOfEdges++;
    }

    template <typename T>
    void Graph<T>::addEdge(int first, int second, int weight) {
        assert(first < amountOfVertices && second < amountOfVertices);
        if (changeEdgeWeight(first, second, weight)) {
            return;
        }
        edges.push_back(Edge(first, second, weight));
        amountOfEdges++;
    }

    template <typename T>
    bool Graph<T>::changeEdgeWeight(int first, int second, int weight) {
        assert(first < amountOfVertices && second < amountOfVertices);
        int edgeIndex = getEdgeIndex(first, second);
        if (edgeIndex != -1) {
            edges[edgeIndex].weight = weight;
            return true;
        }
        return false;
    }

    template <typename T>
    const std::vector<T>& Graph<T>::getInfo() const {
        return info;
    }

    template <typename T>
    int Graph<T>::getAmountOfVertices() const {
        return amountOfVertices;
    }

    template <typename T>
    int Graph<T>::getAmountOfEdges() const {
        return amountOfEdges;
    }

    template <typename T>
    const std::vector<typename Graph<T>::Edge>& Graph<T>::getEdges() const {
        return edges;
    }

    template <typename T>
    const typename Graph<T>::Edge& Graph<T>::getEdge(int index) const {
        return edges[index];
    }

    template <typename T>
    bool Graph<T>::isConnected(int first, int second) const {
        for (auto item : edges) {
            if (item.from == first && item.to == second) {
                return true;
            }
        }
        return false;
    }

    template <typename T>
    void Graph<T>::print() {
        for (auto item : edges) {
            std::cout << item.from << "(" << info[item.from] << ")" << " --(" << item.weight
                      << ")-- " << item.to << "(" << info[item.to] << ")" << std::endl;
        }
    }
}