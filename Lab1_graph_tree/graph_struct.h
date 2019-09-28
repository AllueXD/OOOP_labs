#ifndef LAB1_GRAPH_TREE_GRAPH_STRUCT_H
#define LAB1_GRAPH_TREE_GRAPH_STRUCT_H

#include<iostream>
#include<vector>
#include<ctime>
#include<queue>
#include<algorithm>

using namespace std;

class Graph_Struct {
private:
    vector<vector<pair<int,int>>> adjacent;
    int vertex_count;
    bool is_oriented = false;

public:
    explicit Graph_Struct(int vert_count, bool oriented = false)
            : is_oriented(oriented), vertex_count(vert_count) {
        adjacent.resize(vert_count);
    }

    void output_graph() {
        for (int i = 0; i < vertex_count; i++) {
            cout<<i<<": ";
            for (auto item : adjacent[i]) {
                cout<<'('<<item.first<<", "<<item.second<<") ";
            }
            cout<<endl;
        }
    }

    void add_edge(int vert1, int vert2, int weight = 1) {
        bool already_in_graph = false;
        for (int edge = 0; edge < adjacent[vert1].size(); edge++) {
            if (adjacent[vert1][edge].first == vert2) {
                already_in_graph = true;
                adjacent[vert1][edge].second = weight;
                if (!is_oriented) {
                    for (int i = 0; i < adjacent[vert2].size(); i++) {
                        if (adjacent[vert2][i].first == vert1) {
                            adjacent[vert2][i].second = weight;
                        }
                    }
                }
            }
        }
        if (!already_in_graph) {
            adjacent[vert1].push_back(make_pair(vert2, weight));
            if (!is_oriented) {
                adjacent[vert2].push_back(make_pair(vert1, weight));
            }
        }
    }
    void add_vertex () {
        vertex_count++;
        adjacent.resize(adjacent.size()+1);
    }

    void delete_edge (int vert1, int vert2) {

        for (int i = 0; i < adjacent.at(vert1).size(); i++) {
            if (adjacent.at(vert1)[i].first == vert2) {
                adjacent.at(vert1).erase(adjacent.at(vert1).begin() + i);
            }
        }
        if (!is_oriented) {
            for (int i = 0; i < adjacent.at(vert2).size(); i++) {
                if (adjacent.at(vert2)[i].first == vert1) {
                    adjacent.at(vert2).erase(adjacent.at(vert2).begin() + i);
                }
            }
        }
    }
    void delete_vertex(int vert) {
        if (vert >= adjacent.size()) {
            cout<<"There is no such vertex to delete"<<endl;
            return;
        }
        adjacent.erase(adjacent.begin()+vert);
        for (auto item_row : adjacent) {
            for (int i = 0; i < item_row.size(); i++) {
                if (item_row[i].first == vert) {
                    item_row.erase(item_row.begin()+i);
                    break;
                }
            }
        }
    }

    void change_oriented (bool change_to) {
        if (change_to == is_oriented) {return;}
        if (!is_oriented) {is_oriented = change_to;}
        else {cout<<"You can't change oriented graph to non-oriented.";}
    }
    void change_edge (int vert1, int vert2, int weight = 1) {
        if (weight < 0) {cout<<"Weight of edge can't be lower then 0";}
        else {
            for (int i = 0; i < adjacent.at(vert1).size(); i++) {
                if (adjacent.at(vert1)[i].first == vert2) {
                    adjacent.at(vert1)[i].second = weight;
                }
            }
            if (!is_oriented) {
                for (int i = 0; i < adjacent.at(vert2).size(); i++) {
                    if (adjacent.at(vert2)[i].first == vert1) {
                        adjacent.at(vert2)[i].second = weight;
                    }
                }
            }
        }
    }

    int get_edge_index (int vert1, int vert2) const {
        return adjacent.at(vert1).at(vert2).second;
    }
    int get_edge (int vert1, int vert2) const {
        for (auto item : adjacent.at(vert1)) {
            if (item.first == vert2) {
                return item.second;
            }
        }
        return 0;
    }
    int get_vertex_count () const {
        return vertex_count;
    }
    bool get_is_oriented () const {
        return is_oriented;
    }
    int get_row_size(int vert) const {
        return adjacent.at(vert).size();
    }
    int get_connected (int vert1, int index) const {
        return adjacent.at(vert1).at(index).first;
    }
    pair<int,int> get_pair (int vert1, int index) const {
        return adjacent.at(vert1).at(index);
    }

};

Graph_Struct* create_random_structg(int vertex_count, int edge_count, bool is_oriented = false, bool is_weighed = false) {
    Graph_Struct* graph = new Graph_Struct(vertex_count);
    (*graph).change_oriented(is_oriented);

    int vert1, vert2, weight = 1;
    bool used;
    for (int i = 0; i < edge_count; i++) {
        do {
            used = false;
            vert1 = rand() % vertex_count;
            vert2 = rand() % vertex_count;
            while (vert1 == vert2) {vert2 = rand()%vertex_count;}
            for (int j = 0; j < (*graph).get_row_size(vert1); j++) {
                if ((*graph).get_connected(vert1,j) == vert2) {
                    used = true;
                }
            }
        } while (used);

        if (is_weighed) {weight = rand()%9+1;}
        (*graph).add_edge(vert1,vert2,weight);
    }
    return graph;
}

/*bool is_cyclic_struct_rec(int curr_vertex, bool* visited, bool *recStack, Graph_Struct& graph) {
    if(!visited[curr_vertex]) {

        visited[curr_vertex] = true;
        recStack[curr_vertex] = true;

        for(int i = 0; i < graph.get_row_size(curr_vertex); i++) {
            if (!visited[graph.get_connected(curr_vertex,i)]
                && is_cyclic_struct_rec(graph.get_connected(curr_vertex,i), visited, recStack, graph)) {return true;}
            else if (recStack[graph.get_connected(curr_vertex,i)]) {return true;}
        }

    }
    recStack[curr_vertex] = false;
    return false;
}
bool is_cyclic_str (Graph_Struct& graph) {
    bool visited[max_vert_count];
    bool stack[max_vert_count];

    for (int i = 0; i < graph.get_vertex_count(); i++) {
        visited[i] = false;
        stack[i] = false;
    }

    for (int i = 0; i < graph.get_vertex_count(); i++) {
        if (is_cyclic_struct_rec(i,visited,stack,graph)) {return true;}
    }
    return false;
}*/

bool compare_weight (pair<int,int> left, pair<int,int> right) {
    return left.second<right.second;
}

//bypass for tree
void bfs_struct_rec(int curr_vertex, vector<bool>& visited, Graph_Struct& graph, bool by_weight = false) {
    queue<int> q;
    vector<pair<int,int>> edges_weight;

    visited[curr_vertex] = true;
    q.push(curr_vertex);

    while(!q.empty()) {
        curr_vertex = q.front();
        cout << curr_vertex << " ";
        q.pop();

        for (int i = 0; i < graph.get_row_size(curr_vertex); i++) {
            edges_weight.push_back(graph.get_pair(curr_vertex,i));
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
void bfs_struct(Graph_Struct& graph, bool by_weight = false) {
    vector<bool> visited(graph.get_vertex_count(), false);
    for (int curr_vertex = 0; curr_vertex < graph.get_vertex_count(); curr_vertex++) {
        if (visited[curr_vertex] == false) {bfs_struct_rec(curr_vertex, visited, graph, by_weight);}
    }
    cout<<endl;
}

//spanning tree
Graph_Struct* bfs_struct_for_span(Graph_Struct& graph, bool by_weight = false) {
    queue<int> q;
    vector<pair<int, int>> edges_weight;
    vector<bool> already_connected;
    auto result = new Graph_Struct(graph.get_vertex_count());
    vector<bool> visited;

    for (int i = 0; i < graph.get_vertex_count(); i++) {
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

        for (int i = 0; i < graph.get_row_size(curr_vertex); i++) {
            if (!already_connected[graph.get_connected(curr_vertex, i)]) {
                (*result).add_edge(curr_vertex, graph.get_connected(curr_vertex,i), graph.get_edge_index(curr_vertex,i));
                if (!graph.get_is_oriented()) {(*result).add_edge(graph.get_connected(curr_vertex,i), curr_vertex, graph.get_edge_index(curr_vertex,i)); }
                already_connected[graph.get_connected(curr_vertex,i)] = true;
            }
        }

        for (int i = 0; i < graph.get_row_size(curr_vertex); i++) {
            edges_weight.push_back(graph.get_pair(curr_vertex,i));
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

//minimum spanning tree
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
Graph_Struct* boruvka_struct(Graph_Struct& graph) {
    Graph_Struct* result = new Graph_Struct(graph.get_vertex_count());
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
            for (int i = 0; i < graph.get_row_size(vert); i++) {
                if (graph.get_pair(vert,i).second < min_edge
                    && find_subset_by_vert(subsets, vert, amount_of_component) !=
                       find_subset_by_vert(subsets, graph.get_pair(vert,i).first, amount_of_component)) {
                    min_edge = graph.get_pair(vert,i).second;
                    lowest[vert] = graph.get_pair(vert,i);
                }
            }
        }

        for (int i = 0; i < amount_of_component; i++) {
            pair<int, int> verts_for_union = lowest_in_subset(&subsets[i], lowest);
            int new_edge_weight = 0;
            for (int j = 0; j < graph.get_row_size(verts_for_union.first); j++) {
                if (graph.get_pair(verts_for_union.first,j).first == verts_for_union.second) {
                    new_edge_weight = graph.get_pair(verts_for_union.first,i).second;
                }
            }
            bool already_in_graph = false;
            for (int edge = 0; edge < (*result).get_row_size(verts_for_union.first); edge++) {
                if ((*result).get_pair(verts_for_union.first,edge).first == verts_for_union.second) {
                    already_in_graph = true;
                }
            }
            if (!already_in_graph) {
                (*result).add_edge(verts_for_union.first,verts_for_union.second, new_edge_weight);
                (*result).add_edge(verts_for_union.second,verts_for_union.first, new_edge_weight);
                union_subsets(subsets, verts_for_union.first, verts_for_union.second, &amount_of_component);
            }
        }
    }
    return result;
}

//weight to check if spanning tree is minimum
int weight_of_struct_graph (Graph_Struct& graph) {
    int weight = 0;

    for (int i = 0; i < graph.get_vertex_count(); i++) {
        for (int j = 0; j < graph.get_row_size(i); j++){
            weight += graph.get_pair(i,j).second;
        }
    }
    return weight/2;
}

#endif //LAB1_GRAPH_TREE_GRAPH_STRUCT_H
