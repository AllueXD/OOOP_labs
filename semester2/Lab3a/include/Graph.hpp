#pragma once

#include <vector>
#include <cassert>

namespace graph {

    template<typename T>
    class Graph {
    public:
        struct Edge {
            int from;
            int to;
            int weight;

            Edge(int _from, int _to, int _weight) : from(_from), to(_to), weight(_weight) {}
        };

    private:
        int amountOfVertices = 0;
        int amountOfEdges = 0;

        std::vector<Edge> edges;
        std::vector<T> info;

        int getEdgeIndex(int first, int second);
        void changeEdgeWeight(int index, int weight);

    public:
        Graph() = default;
        explicit Graph(const std::vector<T> &_info);
        Graph(const Graph &graph);
        explicit Graph(std::initializer_list<T> elems);

        void addVertex(const T& vertInfo);
        void eraseVertex(int index);

        void addEdge(int first, int second, int weight);
        bool changeEdgeWeight(int first, int second, int weight);
        void eraseEdge(int first, int second);

        const std::vector<T>& getInfo() const;
        int getAmountOfVertices() const;
        int getAmountOfEdges() const;
        const std::vector<Edge>& getEdges() const;

        bool isConnected(int first, int second) const;
        void print();
    };
}

#include "../src/Graph.tpp"
