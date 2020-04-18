#include <iostream>

#include "include/Graph.hpp"
#include "include/GraphAlgorithms.hpp"


int main() {
    graph::Graph<int> graph;
    for (int i = 0; i < 9; i++) {
        graph.addVertex(i);
    }
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 7, 8);
    graph.addEdge(1, 2, 8);
    graph.addEdge(1, 7, 11);
    graph.addEdge(2, 3, 7);
    graph.addEdge(2, 8, 2);
    graph.addEdge(2, 5, 4);
    graph.addEdge(3, 4, 9);
    graph.addEdge(3, 5, 14);
    graph.addEdge(4, 5, 10);
    graph.addEdge(5, 6, 2);
    graph.addEdge(6, 7, 1);
    graph.addEdge(6, 8, 6);
    graph.addEdge(7, 8, 7);

    graph.print();

    std::vector<std::vector<int>> johnsonRes = graph::algorithm::Johnson(graph);
    for (int i = 0; i < graph.getAmountOfVertices(); i++) {
        graph::algorithm::utilities::printDistances(graph, johnsonRes[i], i);
    }

    return 0;
}