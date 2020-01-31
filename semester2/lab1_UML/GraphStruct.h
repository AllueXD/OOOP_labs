//
// Created by yana4bka on 1/28/20.
//

#ifndef LAB1_GRAPHSTRUCT_H
#define LAB1_GRAPHSTRUCT_H

#include <iostream>
#include<vector>
#include <ctime>
#include<queue>
#include<algorithm>
#include<string>
#include<fstream>
#include "MutualFunctions.h"

using namespace std;

struct graph_struct {
    vector<vector<pair<int,int>>> adjacent;
    int vertex_count;
    bool is_oriented = false;

    explicit graph_struct(int vertices) {
        vertex_count = vertices;
        adjacent.resize(vertices);
    }
};

void add_to_struct (graph_struct& graph, int vert1, int vert2, int weight = 1) {
    bool already_in_graph = false;
    for (int edge = 0; edge < (graph).adjacent[vert1].size(); edge++) {
        if ((graph).adjacent[vert1][edge].first == vert2) {
            already_in_graph = true;
            (graph).adjacent[vert1][edge].second = weight;
            if (!graph.is_oriented) {
                for (int i = 0; i < graph.adjacent[vert2].size(); i++) {
                    if (graph.adjacent[vert2][i].first == vert1) {
                        (graph).adjacent[vert2][i].second = weight;
                    }
                }
            }
        }
    }
    if (!already_in_graph) {
        graph.adjacent[vert1].push_back(make_pair(vert2, weight));
        if (!graph.is_oriented) {
            graph.adjacent[vert2].push_back(make_pair(vert1, weight));
        }
    }
};

void output_struct_graph (graph_struct& graph) {
    for (int i = 0; i < graph.vertex_count; i++) {
        cout<<i<<": ";
        for (auto item : graph.adjacent[i]) {
            cout<<'('<<item.first<<", "<<item.second<<") ";
        }
        cout<<endl;
    }
}

graph_struct* create_random_structg(int vertex_count, int edge_count, bool is_oriented = false, bool is_weighed = false) {
    graph_struct* graph = new graph_struct(vertex_count);
    (*graph).is_oriented = is_oriented;

    int vert1, vert2, weight = 1;
    bool used;
    for (int i = 0; i < edge_count; i++) {
        do {
            used = false;
            vert1 = rand() % vertex_count;
            vert2 = rand() % vertex_count;
            while (vert1 == vert2) {vert2 = rand()%vertex_count;}
            for (int j = 0; j < (*graph).adjacent[vert1].size(); j++) {
                if (((*graph).adjacent[vert1])[j].first == vert2) {
                    used = true;
                }
            }
        } while (used);

        if (is_weighed) {weight = rand()%9+1;}
        (*graph).adjacent[vert1].push_back(make_pair(vert2, weight));
        if (!is_oriented) {
            (*graph).adjacent[vert2].push_back(make_pair(vert1, weight));
        }
    }
    return graph;
}

bool is_cyclic_struct_rec(int curr_vertex, bool* visited, bool *recStack, graph_struct& graph) {
    if(!visited[curr_vertex]) {

        visited[curr_vertex] = true;
        recStack[curr_vertex] = true;

        for(int i = 0; i < graph.adjacent[curr_vertex].size(); i++) {
            if (!visited[graph.adjacent[curr_vertex][i].first]
                && is_cyclic_struct_rec(graph.adjacent[curr_vertex][i].first, visited, recStack, graph)) {return true;}
            else if (recStack[graph.adjacent[curr_vertex][i].first]) {return true;}
        }

    }
    recStack[curr_vertex] = false;
    return false;
}
bool is_cyclic_str (graph_struct& graph) {
    bool visited[max_vert_count];
    bool stack[max_vert_count];

    for (int i = 0; i < graph.vertex_count; i++) {
        visited[i] = false;
        stack[i] = false;
    }

    for (int i = 0; i < graph.vertex_count; i++) {
        if (is_cyclic_struct_rec(i,visited,stack,graph)) {return true;}
    }
    return false;
}

void bfs_struct_rec(int curr_vertex, vector<bool>& visited, graph_struct& graph, bool by_weight = false) {
    queue<int> q;
    vector<pair<int,int>> edges_weight;

    visited[curr_vertex] = true;
    q.push(curr_vertex);

    while(!q.empty()) {
        curr_vertex = q.front();
        cout << curr_vertex << " ";
        q.pop();

        for (int i = 0; i < graph.adjacent[curr_vertex].size(); i++) {
            edges_weight.push_back(graph.adjacent[curr_vertex][i]);
        }
        if (by_weight) {sort(edges_weight.begin(), edges_weight.end(),compare_weight);}

        for (int i = 0; i < edges_weight.size(); i++) {
            if (!visited[edges_weight[i].first]) {
                visited[edges_weight[i].first] = true;
                q.push(edges_weight[i].first);
            }
        }
    }
}
void bfs_struct(graph_struct& graph, bool by_weight = false) {
    vector<bool> visited(max_vert_count, false);
    for (int curr_vertex = 0; curr_vertex < graph.vertex_count; curr_vertex++) {
        if (visited[curr_vertex] == false) {bfs_struct_rec(curr_vertex, visited, graph, by_weight);}
    }
    cout<<endl;
}

vector<vector<int>> Floyd_struct (graph_struct& graph) {
    vector<vector<int>> distance;

    int matrix[max_vert_count][max_vert_count];
    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.vertex_count; j++) {
            if (i==j) {
                matrix[i][j] = 0;
            } else {
                matrix[i][j] = 1000000;
            }
        }
    }

    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.adjacent[i].size(); j++) {
            matrix[i][graph.adjacent[i][j].first] = graph.adjacent[i][j].second;
        }
    }

    for (int k = 0; k < graph.vertex_count; k++) {
        for (int i = 0; i < graph.vertex_count; i++) {
            for (int j = 0; j < graph.vertex_count; j++) {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }
    for (int i = 0; i < graph.vertex_count; i++) {
        vector<int> row;
        for (int j = 0; j < graph.vertex_count; j++) {
            if (matrix[i][j] == 1000000) {matrix[i][j] = 0;}
            row.push_back(matrix[i][j]);
        }
        distance.push_back(row);
    }
    return distance;
}
vector<int> Floyd_struct_all_for_one (graph_struct& graph, int vertex) {
    vector<vector<int>> distance;
    vector<int> result;
    distance = Floyd_struct(graph);
    for (int i = 0; i < graph.vertex_count; i++) {
        result.push_back(distance[vertex][i]);
    }
    return result;
}
int Floyd_struct_between_two (graph_struct& graph, int vertex1, int vertex2) {
    vector<vector<int>> distance = Floyd_struct(graph);
    return (distance[vertex1][vertex2]);
}

void dfs_for_topological_struct(graph_struct& graph, int vertex, vector<bool>& visited, vector<int>& result) {

    visited[vertex] = true;
    for (int i = 0; i < graph.adjacent[vertex].size(); i++) {
        if (!visited[graph.adjacent[vertex][i].first]) {
            dfs_for_topological_struct(graph, graph.adjacent[vertex][i].first, visited, result);
        }
    }

    result.push_back(vertex);
}
vector<int> topological_sort_struct(graph_struct& graph) {
    vector<bool> visited;
    vector<int> result;

    if (!graph.is_oriented || is_cyclic_str(graph)) {
        cout<<"This graph is not acyclic and directed"<<endl;
        return result;
    }

    for (int i = 0; i < graph.vertex_count; i++) {visited.push_back(false);}
    for (int i = 0; i < graph.vertex_count; i++) {
        if (!visited[i])
            dfs_for_topological_struct(graph, i, visited, result);
    }
    reverse(result.begin(), result.end());
    return result;
}

graph_struct* bfs_struct_for_span(graph_struct& graph, bool by_weight = false) {
    queue<int> q;
    vector<pair<int, int>> edges_weight;
    vector<bool> already_connected;
    graph_struct* result = new graph_struct(graph.vertex_count);
    vector<bool> visited;

    for (int i = 0; i < graph.vertex_count; i++) {
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

        for (int i = 0; i < graph.adjacent[curr_vertex].size(); i++) {
            if (!already_connected[graph.adjacent[curr_vertex][i].first]) {
                (*result).adjacent[curr_vertex].push_back(graph.adjacent[curr_vertex][i]);
                if (!graph.is_oriented) {(*result).adjacent[graph.adjacent[curr_vertex][i].first].push_back(make_pair(curr_vertex,graph.adjacent[curr_vertex][i].second));}
                already_connected[graph.adjacent[curr_vertex][i].first] = true;
            }
        }

        for (int i = 0; i < graph.adjacent[curr_vertex].size(); i++) {
            edges_weight.push_back(graph.adjacent[curr_vertex][i]);
        }
        if (by_weight) {sort(edges_weight.begin(), edges_weight.end());}

        for (int i = 0; i < edges_weight.size(); i++) {
            if (!visited[edges_weight[i].first]) {
                visited[edges_weight[i].first] = true;
                q.push(edges_weight[i].first);
            }
        }
    }
    return result;
}

graph_struct* boruvka_struct(graph_struct& graph) {
    graph_struct* result = new graph_struct(graph.vertex_count);
    vector<boruvka_subset> subsets;
    vector<pair<int, int>> lowest;

    for (int vert = 0; vert < graph.vertex_count; vert++){
        boruvka_subset new_sub = *new boruvka_subset;
        pair<int,int> new_pair = *new pair<int,int>;
        subsets.push_back(new_sub);
        lowest.push_back(new_pair);
        subsets[vert].vertexes.push_back(vert);
    }

    int amount_of_component = graph.vertex_count;

    while (amount_of_component > 1) {
        for (int vert = 0; vert < graph.vertex_count; vert++) {
            int min_edge = INT32_MAX;
            for (int i = 0; i < graph.adjacent[vert].size(); i++) {
                if (graph.adjacent[vert][i].second < min_edge
                    && find_subset_by_vert(subsets, vert, amount_of_component) !=
                       find_subset_by_vert(subsets, graph.adjacent[vert][i].first, amount_of_component)) {
                    min_edge = graph.adjacent[vert][i].second;
                    lowest[vert] = make_pair(graph.adjacent[vert][i].first, graph.adjacent[vert][i].second);
                }
            }
        }

        for (int i = 0; i < amount_of_component; i++) {
            pair<int, int> verts_for_union = lowest_in_subset(&subsets[i], lowest);
            int new_edge_weight = 0;
            for (int j = 0; j < graph.adjacent[verts_for_union.first].size(); j++) {
                if (graph.adjacent[verts_for_union.first][j].first == verts_for_union.second) {
                    new_edge_weight = graph.adjacent[verts_for_union.first][j].second;
                }
            }
            bool already_in_graph = false;
            for (int edge = 0; edge < (*result).adjacent[verts_for_union.first].size(); edge++) {
                if ((*result).adjacent[verts_for_union.first][edge].first == verts_for_union.second) {
                    already_in_graph = true;
                }
            }
            if (!already_in_graph) {
                (*result).adjacent[verts_for_union.first].push_back(make_pair(verts_for_union.second, new_edge_weight));
                (*result).adjacent[verts_for_union.second].push_back(make_pair(verts_for_union.first, new_edge_weight));
                union_subsets(subsets, verts_for_union.first, verts_for_union.second, &amount_of_component);
            }
        }
    }
    return result;
}

int weight_of_struct_graph (graph_struct& graph) {
    int weight = 0;

    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.adjacent[i].size(); j++){
            weight += graph.adjacent[i][j].second;
        }
    }
    return weight/2;
}

#endif //LAB1_GRAPHSTRUCT_H
