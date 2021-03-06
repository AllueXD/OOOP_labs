#ifndef NEWVERSION_GRAPHALGORITHMS_H
#define NEWVERSION_GRAPHALGORITHMS_H

#include "Graph.h"
#include "GraphStruct.h"
#include "GraphMatrix.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include <memory>
#include <type_traits>
#include <queue>

/**
 * @brief friend class for GraphMatrix and GraphStruct where implemented all algorithms for graphs
 *
 * In this class implemented common part for both type of graph representation.
 * And this algorithms use method steps from GraphMatrix and GraphStruct that should be different in implementation.
 *
 */
class GraphAlgorithm {
private:
    /**
     * @brief Making random connections in graph
     *
     * @param graph graph in which we adding connection
     * @param _vertex_count amount of vertices in graph
     * @param edge_count amount of new connection that should be added
     * @param is_weighed shows if connection should have weight
     */
    static void random_graph_connection (const std::shared_ptr<Graph>& graph, int _vertex_count, int edge_count, bool is_weighed = false) {
        int vert1, vert2, weight = 1;
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, _vertex_count - 1);

        for (int i = 0; i < edge_count; i++) {
            do {
                vert1 = dist(mt);
                vert2 = dist(mt);
                while (vert1 == vert2) { vert2 = dist(mt); }
            } while (graph->is_connected(vert1, vert2));

            if (is_weighed) {
                std::uniform_int_distribution<int> weight_interval(1, 9);
                weight = weight_interval(mt);
            }
            graph->add_connection(vert1, vert2, weight);
        }
    }

public:

    /**
     * @brief Creating random graph with specified parameters and with specified GraphType
     *
     * @param _vertex_count amount of vertices in new graph
     * @param edge_count amount of connections between vertices in new graph
     * @param _is_oriented orientation of new graph
     * @param is_weighed shows if new graph should be weighed
     *
     * @return graph of specified type
     */
    template <typename GraphType>
    static auto create_random (int _vertex_count, int edge_count, bool _is_oriented = false, bool is_weighed = false) {
        static_assert(std::is_same<GraphType, GraphMatrix>() || std::is_same<GraphType, GraphStruct>(),
                "GraphType for random graph is unknown");
        if (_is_oriented) {
            assert(edge_count <= _vertex_count*(_vertex_count - 1));
        }
        else {
            assert(edge_count <= _vertex_count*(_vertex_count - 1)/2);
        }
        auto graph = std::make_shared<GraphType>(_vertex_count, _is_oriented);
        random_graph_connection(graph, _vertex_count, edge_count, is_weighed);
        return graph;
    }

    /**
     * @brief Shows if graph cyclic
     *
     * @return true if graph cyclic and false if acyclic
     */
    static bool is_cyclic (const std::shared_ptr<Graph>& graph)  {
        bool visited[Graph::get_max_vert_count()];
        bool stack[Graph::get_max_vert_count()];

        for (int i = 0; i < graph->get_vertex_count(); i++) {
            visited[i] = false;
            stack[i] = false;
        }

        for (int i = 0; i < graph->get_vertex_count(); i++) {
            if (graph->is_cyclic_rec(i,visited,stack)) {return true;}
        }
        return false;
    }

    /**
    * @brief Making topological sort of graph's vertices
    *
    * Sort all vertices in order of connection without repeating them
    *
    * @return vector with sorted vertices of graph
    */
    static std::vector<int> topological_sort(const std::shared_ptr<Graph>& graph) {
        std::vector<bool> visited;
        std::vector<int> result;

        if (!graph->get_is_oriented() || is_cyclic(graph)) {
            std::cout<<"This graph is not acyclic and directed"<<std::endl;
            return result;
        }

        for (int i = 0; i < graph->get_vertex_count(); i++) {visited.push_back(false);}
        for (int i = 0; i < graph->get_vertex_count(); i++) {
            if (!visited[i])
                graph->dfs_for_topological(i, visited, result);
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    /**
     * @brief Finding minimal distance to all vertices
     *
     * @return matrix where between every two vertices indicated minimal distance
     */
    static std::vector<std::vector<int>> minimal_distances(const std::shared_ptr<Graph>& graph) {
        std::vector<std::vector<int>> distance;

        int matrix[Graph::get_max_vert_count()][Graph::get_max_vert_count()];
        for (int i = 0; i < graph->get_vertex_count(); i++) {
            for (int j = 0; j < graph->get_vertex_count(); j++) {
                if (i==j) {
                    matrix[i][j] = 0;
                } else {
                    if(graph->is_connected(i,j)) {
                        matrix[i][j] = graph->weight_of_connection(i,j);
                    } else {
                        matrix[i][j] = 1000000000;
                    }
                }
            }
        }

        for (int k = 0; k < graph->get_vertex_count(); k++) {
            for (int i = 0; i < graph->get_vertex_count(); i++) {
                for (int j = 0; j < graph->get_vertex_count(); j++) {
                    if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }
                }
            }
        }
        for (int i = 0; i < graph->get_vertex_count(); i++) {
            std::vector<int> row;
            for (int j = 0; j < graph->get_vertex_count(); j++) {
                if (matrix[i][j] == 1000000000) {matrix[i][j] = 0;}
                row.push_back(matrix[i][j]);
            }
            distance.push_back(row);
        }
        return distance;
    }

    /**
     * @brief Finding minimal distance from specified vertex to all other vertices
     *
     * @param vertex vertex for which we searching all minimal vertices
     *
     * @return vector where indicated all minimal distance for specified vertex
     */
    static std::vector<int> minimal_vertex_distances (const std::shared_ptr<Graph>& graph, int vertex)  {
        std::vector<std::vector<int>> distance;
        std::vector<int> result;
        distance = minimal_distances(graph);
        for (int i = 0; i < graph->get_vertex_count(); i++) {
            result.push_back(distance[vertex][i]);
        }
        return result;
    }

    /**
     * @brief Finding minimal distance for two specified vertices
     *
     * @return minimal distance between specified two vertices
     */
    static int minimal_two_vertex_distance(const std::shared_ptr<Graph>& graph, int first_vertex, int second_vertex)  {
        std::vector<std::vector<int>> distance = minimal_distances(graph);
        return (distance[first_vertex][second_vertex]);
    }

    /**
     * @brief Creating spanning tree from graph
     *
     * @param graph graph from which we should create spanning tree
     * @param by_weight flag that shows if we should sort spanning tree by weight
     *
     * @return graph where shows connection for spanning tree from specified graph
     */
    template <typename GraphType>
    static auto spanning_tree_BFS (const std::shared_ptr<GraphType>& graph, bool by_weight = false) {
        static_assert(std::is_same<GraphType, GraphMatrix>() || std::is_same<GraphType, GraphStruct>(),
                "GraphType for random graph is unknown");
        std::queue<int> q;
        std::vector<std::pair<int, int>> edges_weight;
        std::vector<bool> already_connected;
        std::vector<bool> visited;
        auto result = std::make_shared<GraphType>(graph->get_vertex_count(), graph->get_is_oriented());

        for (int i = 0; i < graph->get_vertex_count(); i++) {
            already_connected.push_back(false);
            visited.push_back(false);
        }

        int curr_vertex = 0;
        visited[curr_vertex] = true;
        q.push(curr_vertex);
        already_connected[curr_vertex] = true;

        while(!q.empty()) {
            curr_vertex = q.front();
            q.pop();

            graph->spanning_tree_step(result, curr_vertex, already_connected, edges_weight);
            if (by_weight) {std::sort(edges_weight.begin(), edges_weight.end());}

            for (const auto& item : edges_weight) {
                if (!visited[item.first]) {
                    visited[item.first] = true;
                    q.push(item.first);
                }
            }
        }
        return result;
    }

    /**
     * @brief Creating minimal spanning tree from graph
     *
     * Using Boruvka's algorithm for finding minimal spanning tree.
     *
     * @param graph graph from which we should create spanning tree
     *
     * @return graph where shows connection for minimal spanning tree from specified graph
     */
    template <typename GraphType>
    static auto minimal_spanning_tree (const std::shared_ptr<GraphType>& graph) {
        static_assert(std::is_same<GraphType, GraphMatrix>() || std::is_same<GraphType, GraphStruct>(),
                "GraphType for random graph is unknown");
        auto result = std::make_shared<GraphType>(graph->get_vertex_count(), graph->get_is_oriented());
        std::vector<boruvka_subset> subsets;
        std::vector<std::pair<int, int>> lowest;

        lowest.resize(graph->get_vertex_count());
        subsets.resize(graph->get_vertex_count());
        for (int vert = 0; vert < graph->get_vertex_count(); vert++) {
            subsets[vert].add(vert);
        }

        int amount_of_component = graph->get_vertex_count();

        while (amount_of_component > 1) {
            for (int vert = 0; vert < graph->get_vertex_count(); vert++) {
                graph->min_spanning_tree_step(vert, amount_of_component, subsets, lowest);
            }

            for (int i = 0; i < amount_of_component; i++) {
                std::pair<int, int> verts_for_union = subsets[i].lowest_in_subset(lowest);
                if (!result->is_connected(verts_for_union.first, verts_for_union.second)) {
                    result->add_connection(verts_for_union.first, verts_for_union.second,
                                           graph->weight_of_connection(verts_for_union.first, verts_for_union.second));
                    union_subsets(subsets, verts_for_union.first, verts_for_union.second, &amount_of_component);
                }
            }
        }
        return result;
    }
};




#endif //NEWVERSION_GRAPHALGORITHMS_H
