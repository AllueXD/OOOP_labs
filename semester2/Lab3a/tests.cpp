#define CATCH_CONFIG_MAIN

#include "3rdparty libs/catch.hpp"
#include "include/Graph.hpp"
#include "include/GraphAlgorithms.hpp"
#include <string>

TEST_CASE("Graph", "[graph]") {

    std::vector<std::string> info = {"first", "second", "not fourth", "fourth", "fifth"};
    SECTION ("Graph creation from initializer list") {
        graph::Graph<std::string> graph({"first", "second", "not fourth", "fourth", "fifth"});
        REQUIRE(graph.getAmountOfVertices() == 5);
        REQUIRE(graph.getAmountOfEdges() == 0);
        REQUIRE(graph.getEdges().empty());
        REQUIRE(graph.getInfo() == info);
    }

    graph::Graph<std::string> graph(info);
    SECTION ("Graph creation from vector") {
        REQUIRE(graph.getAmountOfVertices() == 5);
        REQUIRE(graph.getAmountOfEdges() == 0);
        REQUIRE(graph.getEdges().empty());
        REQUIRE(graph.getInfo() == info);
    }

    SECTION ("Adding vertex") {
        graph.addVertex("after fifth");
        REQUIRE(graph.getAmountOfVertices() == 6);
        REQUIRE(graph.getAmountOfEdges() == 0);
        REQUIRE(graph.getEdges().empty());
        info.reserve(5);
        info.emplace_back("after fifth");
        REQUIRE(graph.getInfo() == info);
    }

    SECTION("Adding edges") {
        graph.addEdge(0, 1, 3);
        graph.addEdge(1, 4, -4);
        graph.addEdge(2, 1, 5);
        graph.addEdge(0, 3, -2);
        graph.addEdge(0, 3, -4);
        graph.addEdge(4, 3, -11);

        std::vector<graph::Graph<std::string>::Edge> edges = graph.getEdges();
        REQUIRE(graph.getAmountOfEdges() == 5);
        REQUIRE(edges.size() == 5);
        REQUIRE(edges[0].from == 0);
        REQUIRE(edges[0].to == 1);
        REQUIRE(edges[0].weight == 3);
        REQUIRE(edges[1].from == 1);
        REQUIRE(edges[1].to == 4);
        REQUIRE(edges[1].weight == -4);
        REQUIRE(edges[2].from == 2);
        REQUIRE(edges[2].to == 1);
        REQUIRE(edges[2].weight == 5);
        REQUIRE(edges[3].from == 0);
        REQUIRE(edges[3].to == 3);
        REQUIRE(edges[3].weight == -4);
        REQUIRE(edges[4].from == 4);
        REQUIRE(edges[4].to == 3);
        REQUIRE(edges[4].weight == -11);
    }

    SECTION("Check is connected") {
        REQUIRE(graph.isConnected(0, 1));
        REQUIRE(graph.isConnected(2, 1));
        REQUIRE(graph.isConnected(4, 3));
        REQUIRE(graph.isConnected(0, 2));
        REQUIRE(graph.isConnected(5, 1));
    }

    SECTION("Erase edge") {
        graph.eraseEdge(1, 4);

        std::vector<graph::Graph<std::string>::Edge> edges = graph.getEdges();
        REQUIRE(graph.getAmountOfEdges() == 4);
        REQUIRE(edges.size() == 4);
        REQUIRE(edges[0].from == 0);
        REQUIRE(edges[0].to == 1);
        REQUIRE(edges[0].weight == 3);
        REQUIRE(edges[1].from == 2);
        REQUIRE(edges[1].to == 1);
        REQUIRE(edges[1].weight == 5);
        REQUIRE(edges[2].from == 0);
        REQUIRE(edges[2].to == 3);
        REQUIRE(edges[2].weight == -4);
        REQUIRE(edges[3].from == 4);
        REQUIRE(edges[3].to == 3);
        REQUIRE(edges[3].weight == -11);
    }

    SECTION("Erase vertex") {
        graph.eraseVertex(2);

        REQUIRE(graph.getAmountOfVertices() == 5);
        REQUIRE(graph.getAmountOfEdges() == 3);

        info.erase(info.begin() + 2);
        REQUIRE(graph.getInfo() == info);
        std::vector<graph::Graph<std::string>::Edge> edges = graph.getEdges();
        REQUIRE(edges.size() == 3);
        REQUIRE(edges.size() == 4);
        REQUIRE(edges[0].from == 0);
        REQUIRE(edges[0].to == 1);
        REQUIRE(edges[0].weight == 3);
        REQUIRE(edges[1].from == 0);
        REQUIRE(edges[1].to == 2);
        REQUIRE(edges[1].weight == -4);
        REQUIRE(edges[2].from == 3);
        REQUIRE(edges[2].to == 2);
        REQUIRE(edges[2].weight == -11);
    }

    SECTION("Change edge weight") {
        REQUIRE(graph.changeEdgeWeight(0, 1, 4));
        std::vector<graph::Graph<std::string>::Edge> edges = graph.getEdges();
        REQUIRE(edges.size() == 3);
        REQUIRE(edges[0].weight == 4);
        REQUIRE(edges[1].weight == -4);
        REQUIRE(edges[2].weight == -11);

        REQUIRE(!graph.changeEdgeWeight(0, 3, 4));
        REQUIRE(edges.size() == 3);
        REQUIRE(edges[0].weight == 4);
        REQUIRE(edges[1].weight == -4);
        REQUIRE(edges[2].weight == -11);
    }

    SECTION("Graph creation from another graph") {
        graph::Graph<std::string> graph1(graph);

        REQUIRE(graph1.getAmountOfVertices() == 5);
        REQUIRE(graph1.getAmountOfEdges() == 3);

        REQUIRE(graph1.getInfo() == info);
        std::vector<graph::Graph<std::string>::Edge> edges = graph1.getEdges();
        REQUIRE(edges.size() == 3);
        REQUIRE(edges[0].from == 0);
        REQUIRE(edges[0].to == 1);
        REQUIRE(edges[0].weight == 4);
        REQUIRE(edges[1].from == 0);
        REQUIRE(edges[1].to == 2);
        REQUIRE(edges[1].weight == -4);
        REQUIRE(edges[2].from == 3);
        REQUIRE(edges[2].to == 2);
        REQUIRE(edges[2].weight == -11);
    }

}
