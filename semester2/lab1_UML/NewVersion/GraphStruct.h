#ifndef NEWVERSION_GRAPHSTRUCT_H
#define NEWVERSION_GRAPHSTRUCT_H

#include "Graph.h"
#include "AdditionalBoruvka.h"
#include <iostream>
#include <vector>
#include <memory>

class GraphStruct : public Graph {
    std::vector<std::vector<std::pair<int, int>>> adjacent;
    friend class GraphAlgorithm;

protected:
    bool is_cyclic_rec(int curr_vertex, bool *visited, bool *recStack) const override {
        if(!visited[curr_vertex]) {

            visited[curr_vertex] = true;
            recStack[curr_vertex] = true;

            for(const auto& connected : adjacent[curr_vertex]) {
                if ((!visited[connected.first] && is_cyclic_rec(connected.first, visited, recStack))
                || recStack[connected.first]) {return true;}
            }

        }
        recStack[curr_vertex] = false;
        return false;
    }

    void dfs_for_topological(int vertex, std::vector<bool> &visited, std::vector<int> &result) const override {
        visited[vertex] = true;
        for (const auto& connected : adjacent[vertex]) {
            if (!visited[connected.first]) {
                dfs_for_topological(connected.first, visited, result);
            }
        }

        result.push_back(vertex);
    }

    /**
     * @brief step for creating spanning tree
     *
     * Uses different type of bypass than GraphMatrix
     *
     * @param result result spanning tree
     * @param curr_vertex current vertex that we are checking
     * @param already_connected array that shows which vertices already connected to current
     * @param edges_weight vector with weight of connection from current vertex to any other
     */
    inline void spanning_tree_step (std::shared_ptr<GraphStruct>& result, int curr_vertex,
            std::vector<bool>& already_connected, std::vector<std::pair<int,int>>& edges_weight) const {

        for (int i = 0; i < vertex_count; i++) {
            if (this->is_connected(curr_vertex, i) && !already_connected[i]) {
                result->add_connection(curr_vertex, i, weight_of_connection(curr_vertex, i));
                already_connected[i] = true;
            }
        }

        for (int i = 0; i < vertex_count; i++) {
            if (this->is_connected(curr_vertex, i)) {
                edges_weight.emplace_back(i, this->weight_of_connection(curr_vertex, i));
            }
        }
    }

    /**
     * @brief step for creating minimal spanning tree
     *
     * Defines vertex that has minimal distance to current.
     * Uses different type of bypass than GraphMatrix.
     *
     * @param vert current vertex for which we are searching minimal distance
     * @param amount_of_component current amount of subsets
     * @param subsets current available subsets
     * @param lowest vector of all minimal distances between vertices
     */
    inline void min_spanning_tree_step (int vert, int amount_of_component,
            std::vector<boruvka_subset>& subsets, std::vector<std::pair<int, int>>& lowest) const {

        int min_edge = INT32_MAX;
        std::vector<std::pair<int,int>> connected_to_vertex = this->get_connected_to_vertex(vert);
        for (int i = 0; i < this->get_connected_to_vertex(vert).size(); i++) {
            if (connected_to_vertex[i].second < min_edge
                && find_subset_by_vert(subsets, vert, amount_of_component) !=
                   find_subset_by_vert(subsets, connected_to_vertex[i].first, amount_of_component)) {
                min_edge = connected_to_vertex[i].second;
                lowest[vert] = {connected_to_vertex[i].first, connected_to_vertex[i].second};
            }
        }
    }

public:
    explicit GraphStruct(int _vertex_count, bool _is_oriented = false) : Graph(_vertex_count, _is_oriented) {
        adjacent.resize(_vertex_count);
    }

    void change_oriented(bool oriented) override {
        if (oriented == is_oriented) {return;}
        else {
            if (!oriented) {
                for (int i = 0; i < vertex_count; i++) {
                    for (auto& item : adjacent[i]) {
                        add_connection(item.first, i, item.second);
                    }
                }
            }
            is_oriented = oriented;
        }
    }

    /**
     * @brief Getter for connected vertices to vertex specified by index
     * @param index index of vertex to which we want get connected to
     * @return vector of connected vertices to specified one and weight of every connection
     */
    std::vector<std::pair<int,int>> get_connected_to_vertex(int index) const {
        assert(index < vertex_count);
        return adjacent[index];
    }

    bool is_connected (int vert1, int vert2) const override {
        assert(vert1 < vertex_count && vert2 < vertex_count);
        bool connected = false;
        for (auto& item : adjacent[vert1]) {
            if (item.first == vert2) {connected = true;}
        }
        return connected;
    }

    int weight_of_connection (int vert1, int vert2) const override {
        assert(vert1 < vertex_count && vert2 < vertex_count);
        for (auto& item : adjacent[vert1]) {
            if (item.first == vert2) {return item.second;}
        }
        return 0;
    }

    void add_connection(int vert1, int vert2, int weight = 1) override {
        assert(vert1 < vertex_count && vert2 < vertex_count);
        assert(weight >= 0);
        assert(vert1 != vert2);
        if (is_connected(vert1, vert2)) {
            for (auto& connected : adjacent[vert1]) {
                if (connected.first == vert2) {connected.second = weight;}
            }
        } else {
            adjacent[vert1].emplace_back(vert2, weight);
        }
        if (!is_oriented) {
            if (is_connected(vert2, vert1)) {
                for (auto& connected : adjacent[vert2]) {
                    if (connected.first == vert1) {connected.second = weight;}
                }
            } else {
                adjacent[vert2].emplace_back(vert1,weight);
            }
        }
    }

    void output() const override {
        for (int i = 0; i < vertex_count; i++) {
            std::cout<<i<<": ";
            for (const auto& connected : adjacent[i]) {
                std::cout<<'('<<connected.first<<", "<<connected.second<<") ";
            }
            std::cout<<std::endl;
        }
    }

    int weight_of_graph() const override {
        int weight = 0;

        for (int i = 0; i < vertex_count; i++) {
            for (const auto& connected : adjacent[i]){
                weight += connected.second;
            }
        }
        return weight/2;
    }
};

#endif //NEWVERSION_GRAPHSTRUCT_H


