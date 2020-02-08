//
// Created by yana4bka on 2/7/20.
//
#define CATCH_CONFIG_MAIN
#include "../Catch2/single_include/catch2/catch.hpp"
#include "GraphMatrix.h"
#include "GraphStruct.h"
#include "GraphAlgorithms.h"
#include <algorithm>
#include <vector>

TEST_CASE("GraphStruct", "[GraphStruct]") {
    SECTION("Creating graph") {
        auto graph = std::make_shared<GraphStruct>(10);

        REQUIRE(graph->get_vertex_count() == 10);
        REQUIRE(!graph->get_is_oriented());
        graph->add_connection(3, 5, 1);
        REQUIRE(graph->is_connected(3,5));
        REQUIRE(graph->weight_of_connection(3,5) == 1);
        REQUIRE(graph->is_connected(5,3));
        REQUIRE(graph->weight_of_connection(5,3) == 1);

        graph->change_oriented(true);
        REQUIRE (graph->get_is_oriented());
        graph->add_connection(1,2,10);
        REQUIRE(graph->is_connected(1,2));
        REQUIRE(graph->weight_of_connection(1,2) == 10);
        REQUIRE(!graph->is_connected(2,1));
        REQUIRE(graph->weight_of_connection(2,1) == 0);
        graph->change_oriented(false);
        REQUIRE(graph->is_connected(2,1));
        REQUIRE(graph->weight_of_connection(2,1) == 10);
    }

    SECTION("Cycle check") {
        auto graph = std::make_shared<GraphStruct>(4);
        REQUIRE(!GraphAlgorithm::is_cyclic(graph));
        graph->add_connection(1,2,100);
        graph->add_connection(2,3,100);
        graph->add_connection(3,1,100);
        REQUIRE(GraphAlgorithm::is_cyclic(graph));
    }

    SECTION("Random graph creation") {
        std::shared_ptr<GraphStruct> graph = GraphAlgorithm::create_random<GraphStruct>(3, 3, false);
        REQUIRE(graph->is_connected(0,1));
        REQUIRE(graph->is_connected(0,2));
        REQUIRE(graph->is_connected(1,2));
        REQUIRE(graph->is_connected(2,1));
    }

    auto graph = std::make_shared<GraphStruct>(6, true);
    graph->add_connection(0,1);
    graph->add_connection(0,2);
    graph->add_connection(1,3);
    graph->add_connection(1,4);
    graph->add_connection(2,3);
    graph->add_connection(2,5);
    graph->add_connection(3,4);
    graph->add_connection(3,5);

    SECTION("Topological sort") {
        std::vector<std::vector<int>> variants = {{0,1,2,3,4,5}, {0,1,2,3,5,4}, {0,2,1,3,4,5}, {0,2,1,3,5,4}};
        REQUIRE(std::find(variants.begin(), variants.end(), GraphAlgorithm::topological_sort(graph)) != variants.end());
    }

    SECTION("Floyds algorithm minimal distance") {
        auto little_graph = std::make_shared<GraphStruct>(4, true);
        little_graph->add_connection(0,1,5);
        little_graph->add_connection(0,3,10);
        little_graph->add_connection(1,2,3);
        little_graph->add_connection(2,3,1);
        REQUIRE (GraphAlgorithm::minimal_distances(little_graph) == std::vector<std::vector<int>> {{0,5,8,9}, {0,0,3,4}, {0,0,0,1}, {0,0,0,0}});
        REQUIRE(GraphAlgorithm::minimal_distances(graph) == std::vector<std::vector<int>> {{0,1,1,2,2,2}, {0,0,0,1,1,2}, {0,0,0,1,2,1},
                                                                       {0,0,0,0,1,1}, {0,0,0,0,0,0}, {0,0,0,0,0,0}});
    }

    SECTION("Spanning tree bfs") {
        auto span_graph = GraphAlgorithm::spanning_tree_BFS<GraphStruct>(graph);
        REQUIRE(span_graph->get_connected_to_vertex(0) == std::vector<std::pair<int,int>> {{1,1}, {2,1}});
        REQUIRE(span_graph->get_connected_to_vertex(1) == std::vector<std::pair<int,int>> {{3,1}, {4,1}});
        REQUIRE(span_graph->get_connected_to_vertex(2) == std::vector<std::pair<int,int>> {{5,1}});
        REQUIRE(span_graph->get_connected_to_vertex(3).empty());
        REQUIRE(span_graph->get_connected_to_vertex(4).empty());
        REQUIRE(span_graph->get_connected_to_vertex(5).empty());
    }

    SECTION("Minimal spanning tree Boruvka's algorithm") {
        graph = std::make_shared<GraphStruct>(6, false);
        graph->add_connection(0,1,1);
        graph->add_connection(0,3,4);
        graph->add_connection(1,2,5);
        graph->add_connection(1,3,7);
        graph->add_connection(1,4,3);
        graph->add_connection(1,5,6);
        graph->add_connection(2,5,9);
        graph->add_connection(3,4,8);
        graph->add_connection(4,5,2);

        auto minSpanGraph = GraphAlgorithm::minimal_spanning_tree(graph);
        REQUIRE(minSpanGraph->get_connected_to_vertex(0) == std::vector<std::pair<int,int>> {{1,1}, {3,4}});
        REQUIRE(minSpanGraph->get_connected_to_vertex(1) == std::vector<std::pair<int,int>> {{0,1}, {2,5}, {4,3}});
        REQUIRE(minSpanGraph->get_connected_to_vertex(2) == std::vector<std::pair<int,int>> {{1,5}});
        REQUIRE(minSpanGraph->get_connected_to_vertex(3) == std::vector<std::pair<int,int>> {{0,4}});
        REQUIRE(minSpanGraph->get_connected_to_vertex(4) == std::vector<std::pair<int,int>> {{5,2},{1,3}});
        REQUIRE(minSpanGraph->get_connected_to_vertex(5) == std::vector<std::pair<int,int>> {{4,2}});
    }
}

TEST_CASE("GraphMatrix", "[GraphMatrix]") {
    SECTION("Creating graph") {
        auto graph = std::make_shared<GraphMatrix>(10);

        REQUIRE(graph->get_vertex_count() == 10);
        REQUIRE(!graph->get_is_oriented());
        graph->add_connection(3, 5, 1);
        REQUIRE(graph->is_connected(3,5));
        REQUIRE(graph->weight_of_connection(3,5) == 1);
        REQUIRE(graph->is_connected(5,3));
        REQUIRE(graph->weight_of_connection(5,3) == 1);

        graph->change_oriented(true);
        REQUIRE (graph->get_is_oriented());
        graph->add_connection(1,2,10);
        REQUIRE(graph->is_connected(1,2));
        REQUIRE(graph->weight_of_connection(1,2) == 10);
        REQUIRE(!graph->is_connected(2,1));
        REQUIRE(graph->weight_of_connection(2,1) == 0);
        graph->change_oriented(false);
        REQUIRE(graph->is_connected(2,1));
        REQUIRE(graph->weight_of_connection(2,1) == 10);
    }

    SECTION("Cycle check") {
        auto graph =  std::make_shared<GraphMatrix>(4);
        REQUIRE(!GraphAlgorithm::is_cyclic(graph));
        graph->add_connection(1,2,100);
        graph->add_connection(2,3,100);
        graph->add_connection(3,1,100);
        REQUIRE(GraphAlgorithm::is_cyclic(graph));
    }

    SECTION("Random graph creation") {
        auto graph = GraphAlgorithm::create_random<GraphMatrix>(3, 3, false);
        REQUIRE(graph->is_connected(0,1));
        REQUIRE(graph->is_connected(0,2));
        REQUIRE(graph->is_connected(1,2));
        REQUIRE(graph->is_connected(2,1));
    }

    auto graph = std::make_shared<GraphMatrix>(6, true);
    graph->add_connection(0,1);
    graph->add_connection(0,2);
    graph->add_connection(1,3);
    graph->add_connection(1,4);
    graph->add_connection(2,3);
    graph->add_connection(2,5);
    graph->add_connection(3,4);
    graph->add_connection(3,5);

    SECTION("Topological sort") {
        std::vector<std::vector<int>> variants = {{0,1,2,3,4,5}, {0,1,2,3,5,4}, {0,2,1,3,4,5}, {0,2,1,3,5,4}};
        REQUIRE(std::find(variants.begin(), variants.end(), GraphAlgorithm::topological_sort(graph)) != variants.end());
    }

    SECTION("Floyds algorithm minimal distance") {
        auto little_graph = std::make_shared<GraphMatrix>(4, true);
        little_graph->add_connection(0,1,5);
        little_graph->add_connection(0,3,10);
        little_graph->add_connection(1,2,3);
        little_graph->add_connection(2,3,1);
        REQUIRE (GraphAlgorithm::minimal_distances(little_graph) == std::vector<std::vector<int>> {{0,5,8,9}, {0,0,3,4}, {0,0,0,1}, {0,0,0,0}});
        REQUIRE(GraphAlgorithm::minimal_distances(graph) == std::vector<std::vector<int>> {{0,1,1,2,2,2}, {0,0,0,1,1,2}, {0,0,0,1,2,1},
                                                                                            {0,0,0,0,1,1}, {0,0,0,0,0,0}, {0,0,0,0,0,0}});
    }

    SECTION("Spanning tree bfs") {
        auto span_graph = GraphAlgorithm::spanning_tree_BFS<GraphMatrix>(graph);
        REQUIRE(span_graph->weight_of_connection(0,1) == 1);
        REQUIRE(span_graph->weight_of_connection(0,2) == 1);
        REQUIRE(span_graph->weight_of_connection(1,3) == 1);
        REQUIRE(span_graph->weight_of_connection(1,4) == 1);
        REQUIRE(span_graph->weight_of_connection(2,5) == 1);
        REQUIRE(span_graph->weight_of_connection(0,4) == 0);
    }

    SECTION("Minimal spanning tree Boruvka's algorithm") {
        graph = std::make_shared<GraphMatrix>(6, false);
        graph->add_connection(0,1,1);
        graph->add_connection(0,3,4);
        graph->add_connection(1,2,5);
        graph->add_connection(1,3,7);
        graph->add_connection(1,4,3);
        graph->add_connection(1,5,6);
        graph->add_connection(2,5,9);
        graph->add_connection(3,4,8);
        graph->add_connection(4,5,2);

        auto minSpanGraph = GraphAlgorithm::minimal_spanning_tree(graph);
        REQUIRE(minSpanGraph->weight_of_connection(0,1) == 1);
        REQUIRE(minSpanGraph->weight_of_connection(0,3) == 4);
        REQUIRE(minSpanGraph->weight_of_connection(1,0) == 1);
        REQUIRE(minSpanGraph->weight_of_connection(1,2) == 5);
        REQUIRE(minSpanGraph->weight_of_connection(1,4) == 3);
        REQUIRE(minSpanGraph->weight_of_connection(2,1) == 5);
        REQUIRE(minSpanGraph->weight_of_connection(3,0) == 4);
        REQUIRE(minSpanGraph->weight_of_connection(4,5) == 2);
        REQUIRE(minSpanGraph->weight_of_connection(4,1) == 3);
        REQUIRE(minSpanGraph->weight_of_connection(5,4) == 2);
        REQUIRE(minSpanGraph->weight_of_connection(5,3) == 0);
    }
}