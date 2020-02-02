#ifndef NEWVERSION_GRAPH_H
#define NEWVERSION_GRAPH_H

#include <cassert>
#include <vector>

class Graph {
int vertex_count;
bool is_oriented;
const int MAX_VERTEX_COUNT = 500;

protected:
    Graph(int _vertex_count, bool _is_oriented = false) : is_oriented(_is_oriented){
        assert(_vertex_count > 0);
        vertex_count = _vertex_count;
    }

private:


public:
    virtual void add_connection (int vert1, int vert2, int weight) = 0;
    virtual void output () = 0;
    virtual bool is_cyclic_rec (int curr_vertex, bool* visited, bool *recStack) = 0;
    virtual void is_cyclic () {
        bool visited[MAX_VERTEX_COUNT];
        bool stack[MAX_VERTEX_COUNT];

        for (int i = 0; i < vertex_count; i++) {
            visited[i] = false;
            stack[i] = false;
        }
    }
    virtual void dfs_for_topological (int vertex, std::vector<bool>& visited, std::vector<int>& result) = 0;
    virtual std::vector<int> topological_sort() = 0;
    virtual std::vector<std::vector<int>> minimal_distances () = 0;
    virtual std::vector<int> minimal_vertex_distances () = 0;
    virtual std::vector<int> minimal_two_vertex_distance() = 0;
    virtual int weight_of_graph() = 0;

};

#endif //NEWVERSION_GRAPH_H
