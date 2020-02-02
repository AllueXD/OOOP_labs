
#ifndef LAB1_GRAPHMATRIX_H
#define LAB1_GRAPHMATRIX_H

#include <iostream>
#include<vector>
#include <ctime>
#include<queue>
#include<algorithm>
#include<string>
#include<fstream>
#include "limits"
#include "MutualFunctions.h"

using namespace std;


struct graph_matrix {
    int adjacent[max_vert_count][max_vert_count];
    int vertex_count;
    bool is_oriented = false;

    explicit graph_matrix(int vertices) {
        vertex_count = vertices;
        for (int i = 0; i < vertex_count; i++) {
            for(int j = 0; j < vertex_count; j++) {
                adjacent[i][j] = 0;
            }
        }
    }
};



void add_to_matr (graph_matrix& graph, int vert1, int vert2, int weight = 1) {
    graph.adjacent[vert1][vert2] = weight;
    if (!graph.is_oriented) {
        graph.adjacent[vert2][vert1] = weight;
    }
};

void output_matrix_graph (graph_matrix& graph) {
    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.vertex_count; j++) {
            cout<<graph.adjacent[i][j]<<"  ";
        }
        cout<<endl;
    }
}

graph_matrix* create_random_matrg(int vertex_count, int edge_count, bool is_oriented = false, bool is_weighed = false) {
    graph_matrix* graph = new graph_matrix(vertex_count);
    (*graph).is_oriented = is_oriented;
    int vert1, vert2, weight = 1;
    for (int i = 0; i < edge_count; i++) {
        do {
            vert1 = rand() % vertex_count;
            vert2 = rand() % vertex_count;
            while (vert1 == vert2) {vert2 = rand()%vertex_count;}
        } while ((*graph).adjacent[vert1][vert2]!=0);

        if (is_weighed) {weight = rand()%9+1;}
        (*graph).adjacent[vert1][vert2] = weight;
        if (!is_oriented) {
            (*graph).adjacent[vert2][vert1] = weight;
        }
    }
    return graph;
}

bool is_cyclic_matr_rec(int curr_vertex, bool* visited, bool *recStack, graph_matrix& graph) {
    if (!visited[curr_vertex]) {

        visited[curr_vertex] = true;
        recStack[curr_vertex] = true;

        for (int i = 0; i < graph.vertex_count; i++) {
            if (graph.adjacent[curr_vertex][i] > 0) {
                if (!visited[i] && is_cyclic_matr_rec(i, visited, recStack, graph)) { return true; }
                else if (recStack[i]) { return true; }
            }
        }

    }
    recStack[curr_vertex] = false;
    return false;
}
bool is_cyclic_matr (graph_matrix& graph) {
    bool visited[max_vert_count];
    bool stack[max_vert_count];

    for (int i = 0; i < graph.vertex_count; i++) {
        visited[i] = false;
        stack[i] = false;
    }

    for (int i = 0; i < graph.vertex_count; i++) {
        if (is_cyclic_matr_rec(i,visited,stack,graph)) {return true;}
    }
    return false;
}

void bfs_matr_rec(int curr_vertex, vector<bool>& visited, graph_matrix& graph, bool by_weight = false) {
    queue<int> q;
    vector<pair<int, int>> edges_weight;

    visited[curr_vertex] = true;
    q.push(curr_vertex);

    while(!q.empty()) {
        curr_vertex = q.front();
        cout << curr_vertex << " ";
        q.pop();

        for (int i = 0; i < graph.vertex_count; i++) {
            if (graph.adjacent[curr_vertex][i] > 0) {
                edges_weight.push_back(make_pair(i,graph.adjacent[curr_vertex][i]));
            }
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
void bfs_matr(graph_matrix& graph, bool by_weight) {
    vector<bool> visited(max_vert_count, false);
    for (int curr_vertex = 0; curr_vertex < graph.vertex_count; curr_vertex++) {
        if (visited[curr_vertex] == false) {bfs_matr_rec(curr_vertex, visited, graph, by_weight);}
    }
    cout<<endl;
}



vector<vector<int>> Floyd_matr (graph_matrix& graph) {
    vector<vector<int>> distance;

    int matrix[max_vert_count][max_vert_count];
    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.vertex_count; j++) {
            if (graph.adjacent[i][j] == 0 && i!=j) {
                matrix[i][j] = 1000000;
            } else {
                matrix[i][j] = graph.adjacent[i][j];
            }
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
vector<int> Floyd_matr_all_for_one (graph_matrix& graph, int vertex) {
    vector<vector<int>> distance;
    vector<int> result;
    distance = Floyd_matr(graph);
    for (int i = 0; i < graph.vertex_count; i++) {
        result.push_back(distance[vertex][i]);
    }
    return result;
}
int Floyd_matr_between_two (graph_matrix& graph, int vertex1, int vertex2) {
    vector<vector<int>> distance = Floyd_matr(graph);
    return (distance[vertex1][vertex2]);
}



void dfs_for_topological_matr (graph_matrix& graph, int vertex, vector<bool>& visited, vector<int>& result) {

    visited[vertex] = true;
    for (int i = 0; i < graph.vertex_count; i++) {
        if (graph.adjacent[vertex][i] != 0 && !visited[i])  {
            dfs_for_topological_matr(graph, i, visited, result);
        }
    }

    result.push_back(vertex);
}
vector<int> topological_sort_matr(graph_matrix& graph) {
    vector<bool> visited;
    vector<int> result;

    if (!graph.is_oriented || is_cyclic_matr(graph)) {
        cout<<"This graph is not acyclic and directed"<<endl;
        return result;
    }

    for (int i = 0; i < graph.vertex_count; i++) {visited.push_back(false);}
    for (int i = 0; i < graph.vertex_count; i++) {
        if (!visited[i])
            dfs_for_topological_matr (graph, i, visited, result);
    }
    reverse(result.begin(), result.end());
    return result;
}



graph_matrix* bfs_matr_for_span(graph_matrix& graph, bool by_weight = false) {
    queue<int> q;
    vector<pair<int, int>> edges_weight;
    vector<bool> already_connected;
    vector<bool> visited;
    graph_matrix* result = new graph_matrix(graph.vertex_count);
    int curr_vertex = 0;

    for (int i = 0; i < graph.vertex_count; i++) {
        already_connected.push_back(false);
        visited.push_back(false);
    }

    q.push(curr_vertex);
    already_connected[curr_vertex] = true;

    while(!q.empty()) {
        curr_vertex = q.front();
        q.pop();

        for (int i = 0; i < graph.vertex_count; i++) {
            if (graph.adjacent[curr_vertex][i] != 0 && !already_connected[i]) {
                (*result).adjacent[curr_vertex][i] = graph.adjacent[curr_vertex][i];
                if (!graph.is_oriented) {(*result).adjacent[i][curr_vertex] = graph.adjacent[curr_vertex][i];}
                already_connected[i] = true;
            }
        }

        for (int i = 0; i < graph.vertex_count; i++) {
            if (graph.adjacent[curr_vertex][i] > 0) {
                edges_weight.push_back(make_pair(i,graph.adjacent[curr_vertex][i]));
            }
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

graph_matrix* boruvka_matr(graph_matrix& graph) {

    graph_matrix* result = new graph_matrix(graph.vertex_count);
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
            for (int i = 0; i < graph.vertex_count; i++) {
                if (graph.adjacent[vert][i] < min_edge
                    && find_subset_by_vert(subsets, vert, amount_of_component) !=
                       find_subset_by_vert(subsets, i, amount_of_component) && graph.adjacent[vert][i]!=0) {
                    min_edge = graph.adjacent[vert][i];
                    lowest[vert] = make_pair(i, graph.adjacent[vert][i]);
                }
            }
        }

        for (int i = 0; i < amount_of_component; i++) {
            pair<int, int> verts_for_union = lowest_in_subset(&subsets[i], lowest);
            (*result).adjacent[verts_for_union.first][verts_for_union.second] = graph.adjacent[verts_for_union.first][verts_for_union.second];
            (*result).adjacent[verts_for_union.second][verts_for_union.first] = graph.adjacent[verts_for_union.second][verts_for_union.first];
            union_subsets(subsets, verts_for_union.first, verts_for_union.second, &amount_of_component);
        }

    }
    return result;
}


int weight_of_matr_graph (graph_matrix& graph) {
    int weight = 0;

    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = i+1; j < graph.vertex_count; j++){
            weight += graph.adjacent[i][j];
        }
    }
    return weight;
}

#endif //LAB1_GRAPHMATRIX_H
