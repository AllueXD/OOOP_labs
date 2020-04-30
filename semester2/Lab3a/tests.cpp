#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "3rdparty/doctest.h"
#include "include/Graph.hpp"
#include "include/GraphAlgorithms.hpp"
#include <string>

using namespace graph;

TEST_CASE("Graph") {

    std::vector<std::string> info = {"first", "second", "not fourth", "fourth", "fifth"};
    SUBCASE ("Graph creation from initializer list") {
        Graph<std::string> graph({"first", "second", "not fourth", "fourth", "fifth"});
        REQUIRE(graph.getAmountOfVertices() == 5);
        REQUIRE(graph.getAmountOfEdges() == 0);
        REQUIRE(graph.getEdges().empty());
        REQUIRE(graph.getInfo() == info);
    }

    Graph<std::string> graph(info);
    SUBCASE ("Graph creation from vector") {
        REQUIRE(graph.getAmountOfVertices() == 5);
        REQUIRE(graph.getAmountOfEdges() == 0);
        REQUIRE(graph.getEdges().empty());
        REQUIRE(graph.getInfo() == info);
    }

    SUBCASE ("Adding vertex") {
        graph.addVertex("after fifth");
        REQUIRE(graph.getAmountOfVertices() == 6);
        REQUIRE(graph.getAmountOfEdges() == 0);
        REQUIRE(graph.getEdges().empty());
        info.reserve(5);
        info.emplace_back("after fifth");
        REQUIRE(graph.getInfo() == info);
    }

    graph.addEdge(0, 1, 3);
    graph.addEdge(2, 4, -4);
    graph.addEdge(2, 1, 5);
    graph.addEdge(0, 3, -2);
    graph.addEdge(0, 3, -4);
    graph.addEdge(4, 3, -11);

    SUBCASE("Adding edges") {
        std::vector<Graph<std::string>::Edge> edges = graph.getEdges();
        REQUIRE(graph.getAmountOfEdges() == 5);
        REQUIRE(edges.size() == 5);
        REQUIRE_UNARY(edges[0].from == 0 && edges[0].to == 1 && edges[0].weight == 3);
        REQUIRE_UNARY(edges[1].from == 2 && edges[1].to == 4 && edges[1].weight == -4);
        REQUIRE_UNARY(edges[2].from == 2 && edges[2].to == 1 && edges[2].weight == 5);
        REQUIRE_UNARY(edges[3].from == 0 && edges[3].to == 3 && edges[3].weight == -4);
        REQUIRE_UNARY(edges[4].from == 4 && edges[4].to == 3 && edges[4].weight == -11);
    }

    SUBCASE("Check is connected") {
        REQUIRE(graph.isConnected(0, 1));
        REQUIRE(graph.isConnected(2, 1));
        REQUIRE(graph.isConnected(4, 3));
        REQUIRE(!graph.isConnected(0, 2));
        REQUIRE(!graph.isConnected(5, 1));
    }

    SUBCASE("Erase edge") {
        graph.eraseEdge(2, 4);

        std::vector<Graph<std::string>::Edge> edges = graph.getEdges();
        REQUIRE(graph.getAmountOfEdges() == 4);
        REQUIRE(edges.size() == 4);
        REQUIRE_UNARY(edges[0].from == 0 && edges[0].to == 1 && edges[0].weight == 3);
        REQUIRE_UNARY(edges[1].from == 2 && edges[1].to == 1 && edges[1].weight == 5);
        REQUIRE_UNARY(edges[2].from == 0 && edges[2].to == 3 && edges[2].weight == -4);
        REQUIRE_UNARY(edges[3].from == 4 && edges[3].to == 3 && edges[3].weight == -11);
    }

    SUBCASE("Erase vertex") {
        graph.eraseVertex(2);

        REQUIRE(graph.getAmountOfVertices() == 4);
        REQUIRE(graph.getAmountOfEdges() == 3);

        info.erase(info.begin() + 2);
        REQUIRE(graph.getInfo() == info);
        std::vector<Graph<std::string>::Edge> edges = graph.getEdges();
        REQUIRE(edges.size() == 3);

        REQUIRE_UNARY(edges[0].from == 0 && edges[0].to == 1 && edges[0].weight == 3);
        REQUIRE_UNARY(edges[1].from == 0 && edges[1].to == 2 && edges[1].weight == -4);
        REQUIRE_UNARY(edges[2].from == 3 && edges[2].to == 2 && edges[2].weight == -11);
    }

    SUBCASE("Change edge weight") {
        REQUIRE(graph.changeEdgeWeight(0, 1, 4));
        std::vector<Graph<std::string>::Edge> edges = graph.getEdges();
        REQUIRE(edges.size() == 5);
        REQUIRE(edges[0].weight == 4);
        REQUIRE(edges[1].weight == -4);
        REQUIRE(edges[2].weight == 5);
        REQUIRE(edges[3].weight == -4);
        REQUIRE(edges[4].weight == -11);

        REQUIRE(!graph.changeEdgeWeight(0, 4, 4));
        REQUIRE(edges.size() == 5);
        REQUIRE(edges[0].weight == 4);
        REQUIRE(edges[1].weight == -4);
        REQUIRE(edges[2].weight == 5);
        REQUIRE(edges[3].weight == -4);
        REQUIRE(edges[4].weight == -11);
    }

    SUBCASE("Graph creation from another graph") {
        graph::Graph<std::string> graph1(graph);

        REQUIRE(graph1.getAmountOfVertices() == 5);
        REQUIRE(graph1.getAmountOfEdges() == 5);

        REQUIRE(graph1.getInfo() == info);
        std::vector<Graph<std::string>::Edge> edges = graph1.getEdges();
        REQUIRE_UNARY(edges[0].from == 0 && edges[0].to == 1 && edges[0].weight == 3);
        REQUIRE_UNARY(edges[1].from == 2 && edges[1].to == 4 && edges[1].weight == -4);
        REQUIRE_UNARY(edges[2].from == 2 && edges[2].to == 1 && edges[2].weight == 5);
        REQUIRE_UNARY(edges[3].from == 0 && edges[3].to == 3 && edges[3].weight == -4);
        REQUIRE_UNARY(edges[4].from == 4 && edges[4].to == 3 && edges[4].weight == -11);
    }
}

TEST_CASE("Graph's algorithms for one vertex") {
    SUBCASE("Without cycle") {
        graph::Graph<int> graph({0,1,2,3,4,5,6});
        graph.addEdge(0, 1, 6);
        graph.addEdge(1, 2, 5);
        graph.addEdge(2, 3, 4);
        graph.addEdge(3, 4, 3);
        graph.addEdge(4, 5, 2);
        graph.addEdge(5, 6, 1);

        REQUIRE(algorithm::BellmanFord(graph, 2) == std::vector{INT_MAX, INT_MAX, 0, 4, 7, 9, 10});
        REQUIRE(algorithm::Dijkstra(graph, 2) == std::vector{INT_MAX, INT_MAX, 0, 4, 7, 9, 10});
    }
    SUBCASE("With negative cycle") {
        graph::Graph<int> graph({0,1,2,3,4});
        graph.addEdge(0, 1, 99);
        graph.addEdge(1, 2, 15);
        graph.addEdge(2, 3, 10);
        graph.addEdge(2, 1, -42);
        graph.addEdge(0, 4, -99);

        REQUIRE(algorithm::BellmanFord(graph, 1).empty());
        REQUIRE(algorithm::Johnson(graph).empty());
    }
    SUBCASE("With negative edges") {
        graph::Graph<int> graph({0,1,2,3,4});
        graph.addEdge(0, 1, 1);
        graph.addEdge(1, 3, 2);
        graph.addEdge(3, 4, 3);
        graph.addEdge(0, 2, 10);
        graph.addEdge(2, 3, -10);

        REQUIRE(algorithm::BellmanFord(graph, 2) == std::vector{INT_MAX, INT_MAX, 0, -10, -7});
        REQUIRE(algorithm::Dijkstra(graph, 2) == std::vector{INT_MAX, INT_MAX, 0, -10, -7});
    }
    SUBCASE("Complicated graph") {
        graph::Graph<int> graph({0,1,2,3,4,5,6,7,8,9,10,11,12});
        graph.addEdge(0, 1, 1);
        graph.addEdge(1, 0, 1);
        graph.addEdge(1, 2, 1);
        graph.addEdge(2, 1, 1);
        graph.addEdge(2, 3, 1);
        graph.addEdge(3, 2, 1);
        graph.addEdge(0, 4, 1);
        graph.addEdge(4, 0, 1);
        graph.addEdge(1, 5, 1);
        graph.addEdge(5, 1, 1);
        graph.addEdge(1, 6, 1);
        graph.addEdge(6, 1, 1);
        graph.addEdge(3, 7, 1);
        graph.addEdge(7, 3, 1);
        graph.addEdge(5, 6, 1);
        graph.addEdge(6, 5, 1);
        graph.addEdge(4, 8, 1);
        graph.addEdge(8, 4, 1);
        graph.addEdge(8, 9, 1);
        graph.addEdge(9, 8, 1);
        graph.addEdge(5, 10, 1);
        graph.addEdge(10, 5, 1);
        graph.addEdge(6, 11, 1);
        graph.addEdge(11, 6, 1);
        graph.addEdge(7, 12, 1);
        graph.addEdge(12, 7, 1);
        graph.addEdge(9, 10, 1);
        graph.addEdge(10, 9, 1);
        graph.addEdge(10, 11, 1);
        graph.addEdge(11, 10, 1);
        graph.addEdge(11, 12, 1);
        graph.addEdge(12, 11, 1);

        REQUIRE(algorithm::BellmanFord(graph, 5) == std::vector{2, 1, 2, 3, 3, 0, 1, 4, 3, 2, 1, 2, 3});
        REQUIRE(algorithm::Dijkstra(graph, 5) == std::vector{2, 1, 2, 3, 3, 0, 1, 4, 3, 2, 1, 2, 3});
    }

    SUBCASE("Tree graph") {
        graph::Graph<int> graph({0,1,2,3,4,5});
        graph.addEdge(0, 1, 2);
        graph.addEdge(1, 0, 2);
        graph.addEdge(1, 3, 9);
        graph.addEdge(3, 1, 9);
        graph.addEdge(2, 3, 5);
        graph.addEdge(3, 2, 5);
        graph.addEdge(3, 4, 1);
        graph.addEdge(4, 3, 1);
        graph.addEdge(0, 5, 4);
        graph.addEdge(5, 0, 4);

        REQUIRE(algorithm::BellmanFord(graph, 1) == std::vector{2, 0, 14, 9, 10, 6});
        REQUIRE(algorithm::Dijkstra(graph, 1) == std::vector{2, 0, 14, 9, 10, 6});
    }
}

TEST_CASE("Graph's Johnson algorithm for all vertices") {
    SUBCASE("Non-negative without cycle") {
        graph::Graph<int> graph({0,1,2,3,4,5,6});
        graph.addEdge(0, 1, 6);
        graph.addEdge(1, 2, 5);
        graph.addEdge(2, 3, 4);
        graph.addEdge(3, 4, 3);
        graph.addEdge(4, 5, 2);
        graph.addEdge(5, 6, 1);

        std::vector<std::vector<int>> johnsonResult = algorithm::Johnson(graph);
        REQUIRE(johnsonResult[0] == std::vector{0, 6, 11, 15, 18, 20, 21});
        REQUIRE(johnsonResult[1] == std::vector{INT_MAX, 0, 5, 9, 12, 14, 15});
        REQUIRE(johnsonResult[2] == std::vector{INT_MAX, INT_MAX, 0, 4, 7, 9, 10});
        REQUIRE(johnsonResult[3] == std::vector{INT_MAX, INT_MAX, INT_MAX, 0, 3, 5, 6});
        REQUIRE(johnsonResult[4] == std::vector{INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, 2, 3});
        REQUIRE(johnsonResult[5] == std::vector{INT_MAX, INT_MAX, INT_MAX,
                                                INT_MAX, INT_MAX, 0, 1});
        REQUIRE(johnsonResult[6] == std::vector{INT_MAX, INT_MAX, INT_MAX,
                                                            INT_MAX, INT_MAX, INT_MAX, 0});
    }
    SUBCASE("With negative cycle") {
        graph::Graph<int> graph({0,1,2,3,4});
        graph.addEdge(0, 1, 99);
        graph.addEdge(1, 2, 15);
        graph.addEdge(2, 3, 10);
        graph.addEdge(2, 1, -42);
        graph.addEdge(0, 4, -99);

        REQUIRE(algorithm::Johnson(graph).empty());
    }
    SUBCASE("With negative edges") {
        graph::Graph<int> graph({0, 1, 2, 3});
        graph.addEdge(0, 1, -5);
        graph.addEdge(0, 2, 2);
        graph.addEdge(0, 3, 3);
        graph.addEdge(1, 2, 4);
        graph.addEdge(2, 3, 1);

        std::vector<std::vector<int>> johnsonResult = algorithm::Johnson(graph);
        REQUIRE(johnsonResult[0] == std::vector{0, 0, 0, 0});
        REQUIRE(johnsonResult[1] == std::vector{INT_MAX, 0, 0, 0});
        REQUIRE(johnsonResult[2] == std::vector{INT_MAX, INT_MAX, 0, 0});
        REQUIRE(johnsonResult[3] == std::vector{INT_MAX, INT_MAX, INT_MAX, 0});
    }
}

TEST_CASE("Graph's Johnson algorithm for all vertices: Parallel Version") {
            SUBCASE("Non-negative without cycle") {
        graph::Graph<int> graph({0,1,2,3,4,5,6});
        graph.addEdge(0, 1, 6);
        graph.addEdge(1, 2, 5);
        graph.addEdge(2, 3, 4);
        graph.addEdge(3, 4, 3);
        graph.addEdge(4, 5, 2);
        graph.addEdge(5, 6, 1);

        std::vector<std::vector<int>> johnsonResult = algorithm::Johnson(graph, true);
                REQUIRE(johnsonResult[0] == std::vector{0, 6, 11, 15, 18, 20, 21});
                REQUIRE(johnsonResult[1] == std::vector{INT_MAX, 0, 5, 9, 12, 14, 15});
                REQUIRE(johnsonResult[2] == std::vector{INT_MAX, INT_MAX, 0, 4, 7, 9, 10});
                REQUIRE(johnsonResult[3] == std::vector{INT_MAX, INT_MAX, INT_MAX, 0, 3, 5, 6});
                REQUIRE(johnsonResult[4] == std::vector{INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, 2, 3});
                REQUIRE(johnsonResult[5] == std::vector{INT_MAX, INT_MAX, INT_MAX,
                                                        INT_MAX, INT_MAX, 0, 1});
                REQUIRE(johnsonResult[6] == std::vector{INT_MAX, INT_MAX, INT_MAX,
                                                        INT_MAX, INT_MAX, INT_MAX, 0});
    }
            SUBCASE("With negative cycle") {
        graph::Graph<int> graph({0,1,2,3,4});
        graph.addEdge(0, 1, 99);
        graph.addEdge(1, 2, 15);
        graph.addEdge(2, 3, 10);
        graph.addEdge(2, 1, -42);
        graph.addEdge(0, 4, -99);

                REQUIRE(algorithm::Johnson(graph, true).empty());
    }
            SUBCASE("With negative edges") {
        graph::Graph<int> graph({0, 1, 2, 3});
        graph.addEdge(0, 1, -5);
        graph.addEdge(0, 2, 2);
        graph.addEdge(0, 3, 3);
        graph.addEdge(1, 2, 4);
        graph.addEdge(2, 3, 1);

        std::vector<std::vector<int>> johnsonResult = algorithm::Johnson(graph, true);
                REQUIRE(johnsonResult[0] == std::vector{0, 0, 0, 0});
                REQUIRE(johnsonResult[1] == std::vector{INT_MAX, 0, 0, 0});
                REQUIRE(johnsonResult[2] == std::vector{INT_MAX, INT_MAX, 0, 0});
                REQUIRE(johnsonResult[3] == std::vector{INT_MAX, INT_MAX, INT_MAX, 0});
    }
}