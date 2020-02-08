#ifndef NEWVERSION_GRAPHMATRIX_H
#define NEWVERSION_GRAPHMATRIX_H

#include "Graph.h"
#include "AdditionalBoruvka.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <queue>

class GraphMatrix : public Graph {
    int adjacent[Graph::MAX_VERTEX_COUNT][Graph::MAX_VERTEX_COUNT];
    friend class GraphAlgorithm;

protected:
    bool is_cyclic_rec (int curr_vertex, bool* visited, bool *recStack) const override {
        if (!visited[curr_vertex]) {

            visited[curr_vertex] = true;
            recStack[curr_vertex] = true;

            for (int i = 0; i < vertex_count; i++) {
                if (adjacent[curr_vertex][i] > 0) {
                    if ((!visited[i] && is_cyclic_rec(i, visited, recStack)) || recStack[i]) { return true; }
                }
            }

        }
        recStack[curr_vertex] = false;
        return false;
    }

    void dfs_for_topological (int vertex, std::vector<bool>& visited, std::vector<int>& result) const override {
        visited[vertex] = true;
        for (int i = 0; i < vertex_count; i++) {
            if (adjacent[vertex][i] != 0 && !visited[i])  {
                dfs_for_topological(i, visited, result);
            }
        }
        result.push_back(vertex);
    }

    inline void spanning_tree_step (std::shared_ptr<GraphMatrix>& result, int curr_vertex,
            std::vector<bool>& already_connected, std::vector<std::pair<int,int>>& edges_weight) const {
        for (int i = 0; i < vertex_count; i++) {
            if (this->is_connected(curr_vertex,i) && !already_connected[i]) {
                result->add_connection(curr_vertex, i, this->weight_of_connection(curr_vertex,i));
                already_connected[i] = true;
            }
        }

        for (int i = 0; i < vertex_count; i++) {
            if (this->is_connected(curr_vertex, i)) {
                edges_weight.emplace_back(i, this->weight_of_connection(curr_vertex, i));
            }
        }
    }

    inline void min_spanning_tree_step (int vert, int amount_of_component,
            std::vector<boruvka_subset>& subsets, std::vector<std::pair<int, int>>& lowest) const {

        int min_edge = INT32_MAX;
        for (int i = 0; i < vertex_count; i++) {
            if (this->weight_of_connection(vert, i) < min_edge
                && find_subset_by_vert(subsets, vert, amount_of_component) !=
                   find_subset_by_vert(subsets, i, amount_of_component) && this->is_connected(vert,i)) {
                min_edge = this->weight_of_connection(vert,i);
                lowest[vert] = {i, this->weight_of_connection(vert, i)};
            }
        }
    }

public:
    explicit GraphMatrix(int _vertex_count, bool _is_oriented = false) : Graph(_vertex_count, _is_oriented) {
        for (int i = 0; i < vertex_count; i++) {
            for(int j = 0; j < vertex_count; j++) {
                adjacent[i][j] = 0;
            }
        }
    }

    void change_oriented(bool oriented) {
        if (oriented == is_oriented) {return;}
        else {
            if (!oriented) {
                for (int i = 0; i < vertex_count; i++) {
                    for (int j = 0; j < vertex_count; j++) {
                        if (adjacent[i][j] != 0 && adjacent[j][i] == 0) {
                            add_connection(j,i,adjacent[i][j]);
                        }
                    }
                }
            }
            is_oriented = oriented;
        }
    }

    bool is_connected (int vert1, int vert2) const override {
        assert(vert1 < vertex_count && vert2 < vertex_count);
        return (adjacent[vert1][vert2] > 0);
    }

    int weight_of_connection (int vert1, int vert2) const override {
        assert(vert1 < vertex_count && vert2 < vertex_count);
        return adjacent[vert1][vert2];
    }
    void add_connection (int vert1, int vert2, int weight = 1) override {
        assert(vert1 < vertex_count && vert2 < vertex_count);
        assert(weight >= 0);
        assert(vert1 != vert2);
        adjacent[vert1][vert2] = weight;
        if (!is_oriented) {
            adjacent[vert2][vert1] = weight;
        }
    }

    void output () const override {
        for (int i = 0; i < vertex_count; i++) {
            for (int j = 0; j < vertex_count; j++) {
                std::cout << adjacent[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }

    int weight_of_graph() const override {
        int weight = 0;
        for (int i = 0; i < vertex_count; i++) {
            for (int j = i+1; j < vertex_count; j++){
                weight += adjacent[i][j];
            }
        }
        return weight;
    };
};

#endif //NEWVERSION_GRAPHMATRIX_H
