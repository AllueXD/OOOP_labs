#define CATCH_CONFIG_MAIN
#include "Catch2/single_include/catch2/catch.hpp"
#include "GraphMatrix.h"
#include "GraphStruct.h"
#include "algorithm"
#include "vector"

TEST_CASE("GraphMatrix", "[graph_matrix]") {
    SECTION("Creating graph") {
        auto graph = new graph_matrix(10);

        REQUIRE(graph->vertex_count == 10);
        REQUIRE(!graph->is_oriented);
        add_to_matr(*graph, 3, 5);
        REQUIRE(graph->adjacent[3][5]==1);
        REQUIRE(graph->adjacent[5][3]==1);
        graph->is_oriented = true;
        REQUIRE (graph->is_oriented);
        add_to_matr(*graph, 1, 2, 10);
        REQUIRE(graph->adjacent[1][2]==10);
        REQUIRE(graph->adjacent[2][1]==0);
        add_to_matr(*graph, 11, 2, 13);
        //REQUIRE(graph->adjacent[11][2] == 0);
    }

    SECTION("Cycle check") {
        auto graph = new graph_matrix(0);
        REQUIRE (!is_cyclic_matr(*graph));
        graph = new graph_matrix(4);
        REQUIRE(!is_cyclic_matr(*graph));
        add_to_matr(*graph, 1, 2, 100);
        add_to_matr(*graph, 2, 3, 100);
        add_to_matr(*graph, 3, 1, 100);
        REQUIRE(is_cyclic_matr(*graph));
    }

    SECTION("Random graph creation") {
        auto graph = create_random_matrg(3, 3, false);
        REQUIRE(graph->adjacent[0][1]==1);
        REQUIRE(graph->adjacent[0][2]==1);
        REQUIRE(graph->adjacent[1][2]==1);
        REQUIRE(graph->adjacent[2][1]==1);
    }

    auto graph = new graph_matrix(6);
    graph->is_oriented = true;
    add_to_matr(*graph, 0, 1);
    add_to_matr(*graph, 0, 2);
    add_to_matr(*graph, 1, 3);
    add_to_matr(*graph, 1, 4);
    add_to_matr(*graph, 2, 3);
    add_to_matr(*graph, 2, 5);
    add_to_matr(*graph, 3, 4);
    add_to_matr(*graph, 3, 5);

    SECTION("Topological sort") {
        std::vector<std::vector<int>> variants = {{0,1,2,3,4,5}, {0,1,2,3,5,4}, {0,2,1,3,4,5}, {0,2,1,3,5,4}};
        REQUIRE(std::find(variants.begin(), variants.end(), topological_sort_matr(*graph)) != variants.end());
    }

    SECTION("Floyds algorithm minimal distance") {
        auto little_graph = new graph_matrix(4);
        little_graph->is_oriented = true;
        add_to_matr(*little_graph, 0, 1, 5);
        add_to_matr(*little_graph, 0, 3, 10);
        add_to_matr(*little_graph, 1, 2, 3);
        add_to_matr(*little_graph, 2, 3, 1);
        REQUIRE (Floyd_matr(*little_graph) == std::vector<std::vector<int>> {{0,5,8,9}, {0,0,3,4}, {0,0,0,1}, {0,0,0,0}});
        REQUIRE(Floyd_matr(*graph) == std::vector<std::vector<int>> {{0,1,1,2,2,2}, {0,0,0,1,1,2}, {0,0,0,1,2,1},
                                                                     {0,0,0,0,1,1}, {0,0,0,0,0,0}, {0,0,0,0,0,0}});
    }

    SECTION("Spanning tree bfs") {
        auto span_graph = bfs_matr_for_span(*graph);
        REQUIRE(span_graph->adjacent[0][1] == 1);
        REQUIRE(span_graph->adjacent[0][2] == 1);
        REQUIRE(span_graph->adjacent[1][3] == 1);
        REQUIRE(span_graph->adjacent[1][4] == 1);
        REQUIRE(span_graph->adjacent[2][5] == 1);
        REQUIRE(span_graph->adjacent[2][3] == 0);
        REQUIRE(span_graph->adjacent[3][4] == 0);
        REQUIRE(span_graph->adjacent[3][5] == 0);
    }

    SECTION("Minimal spanning tree Boruvka's algorithm") {
        graph = new graph_matrix(6);
        graph->is_oriented = false;
        add_to_matr(*graph,0,1,1);
        add_to_matr(*graph,0,3,4);
        add_to_matr(*graph,1,2,5);
        add_to_matr(*graph,1,3,7);
        add_to_matr(*graph,1,4,3);
        add_to_matr(*graph,1,5,6);
        add_to_matr(*graph,2,5,9);
        add_to_matr(*graph,3,4,8);
        add_to_matr(*graph,4,5,2);
        auto minSpanGraph = boruvka_matr(*graph);
        REQUIRE(minSpanGraph->adjacent[0][1] == 1);
        REQUIRE(minSpanGraph->adjacent[0][3] == 4);
        REQUIRE(minSpanGraph->adjacent[1][2] == 5);
        REQUIRE(minSpanGraph->adjacent[1][3] == 0);
        REQUIRE(minSpanGraph->adjacent[1][4] == 3);
        REQUIRE(minSpanGraph->adjacent[1][5] == 0);
        REQUIRE(minSpanGraph->adjacent[2][5] == 0);
        REQUIRE(minSpanGraph->adjacent[3][4] == 0);
        REQUIRE(minSpanGraph->adjacent[4][5] == 2);
    }
}

TEST_CASE("GraphStruct", "[graph_struct]") {
    SECTION("Creating graph") {
        auto graph = new graph_struct(10);

        REQUIRE(graph->vertex_count == 10);
        REQUIRE(!graph->is_oriented);
        add_to_struct(*graph, 3, 5);
        REQUIRE(std::find(graph->adjacent[3].begin() ,graph->adjacent[3].end(), std::pair<int,int> {5,1}) != graph->adjacent[3].end());
        REQUIRE(std::find(graph->adjacent[5].begin() ,graph->adjacent[5].end(), std::pair<int,int> {3,1}) != graph->adjacent[5].end());
        graph->is_oriented = true;
        REQUIRE (graph->is_oriented);
        add_to_struct(*graph, 1, 2, 10);
        REQUIRE(std::find(graph->adjacent[1].begin() ,graph->adjacent[1].end(), std::pair<int,int> {2,10}) != graph->adjacent[5].end());
        REQUIRE(std::find(graph->adjacent[2].begin() ,graph->adjacent[2].end(), std::pair<int,int> {1,10}) == graph->adjacent[2].end());
        //add_to_struct(*graph, 11, 2, 13);
        //REQUIRE(std::find(graph->adjacent[11].begin() ,graph->adjacent[11].end(), std::pair<int,int> {2,13}) == graph->adjacent[11].end());
    }

    SECTION("Cycle check") {
        auto graph = new graph_struct(0);
        REQUIRE (!is_cyclic_str(*graph));
        graph = new graph_struct(4);
        REQUIRE(!is_cyclic_str(*graph));
        add_to_struct(*graph, 1, 2, 100);
        add_to_struct(*graph, 2, 3, 100);
        add_to_struct(*graph, 3, 1, 100);
        REQUIRE(is_cyclic_str(*graph));
    }

    SECTION("Random graph creation") {
        auto graph = create_random_structg(3, 3, false);
        REQUIRE(std::find(graph->adjacent[0].begin() ,graph->adjacent[0].end(), std::pair<int,int> {1,1}) != graph->adjacent[0].end());
        REQUIRE(std::find(graph->adjacent[0].begin() ,graph->adjacent[0].end(), std::pair<int,int> {2,1}) != graph->adjacent[0].end());
        REQUIRE(std::find(graph->adjacent[1].begin() ,graph->adjacent[1].end(), std::pair<int,int> {2,1}) != graph->adjacent[1].end());
        REQUIRE(std::find(graph->adjacent[2].begin() ,graph->adjacent[2].end(), std::pair<int,int> {1,1}) != graph->adjacent[2].end());
    }

    auto graph = new graph_struct(6);
    graph->is_oriented = true;
    add_to_struct(*graph, 0, 1);
    add_to_struct(*graph, 0, 2);
    add_to_struct(*graph, 1, 3);
    add_to_struct(*graph, 1, 4);
    add_to_struct(*graph, 2, 3);
    add_to_struct(*graph, 2, 5);
    add_to_struct(*graph, 3, 4);
    add_to_struct(*graph, 3, 5);

    SECTION("Topological sort") {
        std::vector<std::vector<int>> variants = {{0,1,2,3,4,5}, {0,1,2,3,5,4}, {0,2,1,3,4,5}, {0,2,1,3,5,4}};
        REQUIRE(std::find(variants.begin(), variants.end(), topological_sort_struct(*graph)) != variants.end());
    }

    SECTION("Floyds algorithm minimal distance") {
        auto little_graph = new graph_struct(4);
        little_graph->is_oriented = true;
        add_to_struct(*little_graph, 0, 1, 5);
        add_to_struct(*little_graph, 0, 3, 10);
        add_to_struct(*little_graph, 1, 2, 3);
        add_to_struct(*little_graph, 2, 3, 1);
        REQUIRE (Floyd_struct(*little_graph) == std::vector<std::vector<int>> {{0,5,8,9}, {0,0,3,4}, {0,0,0,1}, {0,0,0,0}});
        REQUIRE(Floyd_struct(*graph) == std::vector<std::vector<int>> {{0,1,1,2,2,2}, {0,0,0,1,1,2}, {0,0,0,1,2,1},
                                                                     {0,0,0,0,1,1}, {0,0,0,0,0,0}, {0,0,0,0,0,0}});
    }

    SECTION("Spanning tree bfs") {
        auto span_graph = bfs_struct_for_span(*graph);
        REQUIRE(span_graph->adjacent == std::vector<std::vector<std::pair<int,int>>> { { {1,1}, {2,1} },
                                                                                       { {3,1}, {4,1} },
                                                                                       { {5,1} }, {}, {}, {} });
    }

    SECTION("Minimal spanning tree Boruvka's algorithm") {
        graph = new graph_struct(6);
        graph->is_oriented = false;
        add_to_struct(*graph,0,1,1);
        add_to_struct(*graph,0,3,4);
        add_to_struct(*graph,1,2,5);
        add_to_struct(*graph,1,3,7);
        add_to_struct(*graph,1,4,3);
        add_to_struct(*graph,1,5,6);
        add_to_struct(*graph,2,5,9);
        add_to_struct(*graph,3,4,8);
        add_to_struct(*graph,4,5,2);
        auto minSpanGraph = boruvka_struct(*graph);
        REQUIRE(minSpanGraph->adjacent == std::vector<std::vector<std::pair<int,int>>> { { {1,1}, {3,4} },
                                                                                       { {0,1}, {2,5}, {4,3} },
                                                                                       { {1,5} },
                                                                                       { {0,4} },
                                                                                       { {5,2}, {1,3} },
                                                                                       { {4,2} } });
    }
}
