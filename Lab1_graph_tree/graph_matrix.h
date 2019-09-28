#ifndef LAB1_GRAPH_TREE_GRAPH_MATRIX_H
#define LAB1_GRAPH_TREE_GRAPH_MATRIX_H
#include <iostream>

#include<vector>
#include <ctime>
#include<queue>
#include<algorithm>
#include<string>
#include<fstream>
#include"tm_functions.h"

using namespace std;

const int MAX_VERT_COUNT = 500;

class Graph_Matrix {
    private:
        int adjacent[MAX_VERT_COUNT][MAX_VERT_COUNT];
        int vertex_count = 0;
        bool is_oriented = false;
    public:
    Graph_Matrix(int vert_count, bool oriented = false)
        : is_oriented(oriented), vertex_count(vert_count) {
        for (int i = 0; i < vertex_count; i++) {;
            for(int j = 0; j < vertex_count; j++) {
                adjacent[i][j] = 0;
            }
        }
    }

    void add_to_matr (int vert1, int vert2, int weight = 1) {
        adjacent[vert1][vert2] = weight;
        if (!is_oriented) {
            adjacent[vert2][vert1] = weight;
        }
    }

    void output_matr () {
        for (int i = 0; i < vertex_count; i++) {
            for (int j = 0; j < vertex_count; j++) {
                cout<<adjacent[i][j]<<"  ";
            }
            cout<<endl;
        }
    }
    void delete_edge (int vert1, int vert2) {
        adjacent[vert1][vert2] = 0;
        if (!is_oriented) {adjacent[vert2][vert1] = 0;}
    }
    void change_oriented (bool change_to) {
        if (change_to == is_oriented) {return;}
        if (!is_oriented) {is_oriented = change_to;}
        else {cout<<"You can't change oriented graph to non-oriented.";}
    }
    int get_edge (int vert1, int vert2) const {
        return adjacent[vert1][vert2];
    }
    void change_edge (int vert1, int vert2, int weight = 1) {
        if (weight < 0) {cout<<"Weight of edge can't be lower then 0";}
        else {
            adjacent[vert1][vert2] = weight;
        }
    }
    int get_vertex_count () const {
        return vertex_count;
    }
    bool get_is_oriented () const {
        return is_oriented;
    }
};

Graph_Matrix* create_random_matrg(int vertex_count, int edge_count, bool is_oriented = false, bool is_weighed = false) {
    auto graph = new Graph_Matrix(vertex_count);

    (*graph).change_oriented(is_oriented);
    int vert1, vert2, weight = 1;
    for (int i = 0; i < edge_count; i++) {
        do {
            vert1 = rand() % vertex_count;
            vert2 = rand() % vertex_count;
            while (vert1 == vert2) {vert2 = rand()%vertex_count;}
        } while ((*graph).get_edge(vert1,vert2)!=0);

        if (is_weighed) {weight = rand()%9+1;}
        (*graph).change_edge(vert1,vert2,weight);
        if (!is_oriented) {
            (*graph).change_edge(vert2,vert1,weight);
        }
    }
    return graph;
}

bool is_cyclic_matr_rec(int curr_vertex, bool* visited, bool *recStack, Graph_Matrix& graph) {
    if (!visited[curr_vertex]) {

        visited[curr_vertex] = true;
        recStack[curr_vertex] = true;

        for (int i = 0; i < graph.get_vertex_count(); i++) {
            if (graph.get_edge(curr_vertex,i) > 0) {
                if (!visited[i] && is_cyclic_matr_rec(i, visited, recStack, graph)) { return true; }
                else if (recStack[i]) { return true; }
            }
        }

    }
    recStack[curr_vertex] = false;
    return false;
}
bool is_cyclic_matr (Graph_Matrix& graph) {
    bool visited[MAX_VERT_COUNT];
    bool stack[MAX_VERT_COUNT];

    for (int i = 0; i < graph.get_vertex_count(); i++) {
        visited[i] = false;
        stack[i] = false;
    }

    for (int i = 0; i < graph.get_vertex_count(); i++) {
        if (is_cyclic_matr_rec(i,visited,stack,graph)) {return true;}
    }
    return false;
}
bool compare_weight (pair<int,int> left, pair<int,int> right) {
    return left.second<right.second;
}
void bfs_matr_rec(int curr_vertex, vector<bool>& visited, Graph_Matrix& graph, bool by_weight = false) {
    queue<int> q;
    vector<pair<int, int>> edges_weight;

    visited[curr_vertex] = true;
    q.push(curr_vertex);

    while(!q.empty()) {
        curr_vertex = q.front();
        cout << curr_vertex << " ";
        q.pop();

        for (int i = 0; i < graph.get_vertex_count(); i++) {
            if (graph.get_edge(curr_vertex,i) > 0) {
                edges_weight.emplace_back(i,graph.get_edge(curr_vertex,i));
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
void bfs_matr(Graph_Matrix& graph, bool by_weight) {
    vector<bool> visited(MAX_VERT_COUNT, false);
    for (int curr_vertex = 0; curr_vertex < graph.get_vertex_count(); curr_vertex++) {
        if (visited[curr_vertex] == false) {bfs_matr_rec(curr_vertex, visited, graph, by_weight);}
    }
    cout<<endl;
}

Graph_Matrix* bfs_matr_for_span(Graph_Matrix& graph, bool by_weight = false) {
    queue<int> q;
    vector<pair<int, int>> edges_weight;
    vector<bool> already_connected;
    vector<bool> visited;
    auto result = new Graph_Matrix(graph.get_vertex_count());
    int curr_vertex = 0;

    for (int i = 0; i < graph.get_vertex_count(); i++) {
        already_connected.push_back(false);
        visited.push_back(false);
    }

    q.push(curr_vertex);
    already_connected[curr_vertex] = true;

    while(!q.empty()) {
        curr_vertex = q.front();
        q.pop();

        for (int i = 0; i < graph.get_vertex_count(); i++) {
            if (graph.get_edge(curr_vertex,i) != 0 && !already_connected[i]) {
                (*result).change_edge(curr_vertex,i,graph.get_edge(curr_vertex,i));
                if (!graph.get_is_oriented()) {(*result).change_edge(i,curr_vertex, graph.get_edge(curr_vertex,i));}
                already_connected[i] = true;
            }
        }

        for (int i = 0; i < graph.get_vertex_count(); i++) {
            if (graph.get_edge(curr_vertex,i) > 0) {
                edges_weight.emplace_back(i,graph.get_edge(curr_vertex,i));
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

struct boruvka_subset {
    vector<int> vertexes;
};
pair<int,int> lowest_in_subset (boruvka_subset* sub, vector<pair<int,int>>& lows) {
    int min = lows[sub->vertexes[0]].second;
    pair<int,int> vert_with_min = make_pair(sub->vertexes[0], lows[sub->vertexes[0]].first);
    for (int i = 1; i < sub->vertexes.size(); i++) {
        if (lows[sub->vertexes[i]].second < min) {
            min = lows[sub->vertexes[i]].second;
            vert_with_min = make_pair(sub->vertexes[i], lows[sub->vertexes[i]].first);
        }
    }
    return vert_with_min;
}
int find_subset_by_vert (vector<boruvka_subset>& subs, int vert, int amount_of_component) {
    for (int i = 0; i < amount_of_component; i++) {
        for (int j = 0; j < subs[i].vertexes.size(); j++) {
            if (subs[i].vertexes[j] == vert) { return i; }
        }
    }
}
void union_subsets (vector<boruvka_subset>& subs, int vert1, int vert2, int* amount_of_component) {
    int subset_of_vert1, subset_of_vert2;
    subset_of_vert1 = find_subset_by_vert(subs, vert1, *amount_of_component);
    subset_of_vert2 = find_subset_by_vert(subs, vert2, *amount_of_component);
    if (subset_of_vert1 != subset_of_vert2) {
        for (int i = 0; i < subs[subset_of_vert2].vertexes.size(); i++) {
            subs[subset_of_vert1].vertexes.push_back(subs[subset_of_vert2].vertexes[i]);
        }
        subs.erase(subs.begin() + subset_of_vert2);
        (*amount_of_component)--;
    }
}

Graph_Matrix* boruvka_matr(Graph_Matrix& graph) {

    auto result = new Graph_Matrix(graph.get_vertex_count());
    vector<boruvka_subset> subsets;
    vector<pair<int, int>> lowest;

    for (int vert = 0; vert < graph.get_vertex_count(); vert++){
        boruvka_subset new_sub = *new boruvka_subset;
        pair<int,int> new_pair = *new pair<int,int>;
        subsets.push_back(new_sub);
        lowest.push_back(new_pair);
        subsets[vert].vertexes.push_back(vert);
    }

    int amount_of_component = graph.get_vertex_count();

    while (amount_of_component > 1) {
        for (int vert = 0; vert < graph.get_vertex_count(); vert++) {
            int min_edge = INT32_MAX;
            for (int i = 0; i < graph.get_vertex_count(); i++) {
                if (graph.get_edge(vert,i)< min_edge
                    && find_subset_by_vert(subsets, vert, amount_of_component) !=
                       find_subset_by_vert(subsets, i, amount_of_component) && graph.get_edge(vert,i)!=0) {
                    min_edge = graph.get_edge(vert,i);
                    lowest[vert] = make_pair(i, graph.get_edge(vert,i));
                }
            }
        }

        for (int i = 0; i < amount_of_component; i++) {
            pair<int, int> verts_for_union = lowest_in_subset(&subsets[i], lowest);
            (*result).change_edge(verts_for_union.first,verts_for_union.second,graph.get_edge(verts_for_union.first,verts_for_union.second));
            (*result).change_edge(verts_for_union.second,verts_for_union.first,graph.get_edge(verts_for_union.second,verts_for_union.first));
            union_subsets(subsets, verts_for_union.first, verts_for_union.second, &amount_of_component);
        }

    }
    return result;
}

int weight_of_matr_graph (Graph_Matrix& graph) {
    int weight = 0;

    for (int i = 0; i < graph.get_vertex_count(); i++) {
        for (int j = i+1; j < graph.get_vertex_count(); j++){
            weight += graph.get_edge(i,j);
        }
    }
    return weight;
}

#endif //LAB1_GRAPH_TREE_GRAPH_MATRIX_H
