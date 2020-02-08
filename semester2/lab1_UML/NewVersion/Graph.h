#ifndef NEWVERSION_GRAPH_H
#define NEWVERSION_GRAPH_H

#include <cassert>
#include <vector>
#include "AdditionalBoruvka.h"

class Graph {
protected:
    int vertex_count;
    bool is_oriented;
    static const int MAX_VERTEX_COUNT = 500;
    explicit Graph(int _vertex_count, bool _is_oriented = false) : is_oriented(_is_oriented){
        assert(_vertex_count > 0 && _vertex_count <= MAX_VERTEX_COUNT);
        vertex_count = _vertex_count;
    }

public:
    int get_vertex_count () const {
        return vertex_count;
    }
    bool get_is_oriented () const {
        return is_oriented;
    }
    static int get_max_vert_count () {
        return MAX_VERTEX_COUNT;
    }
    virtual bool is_connected (int vert1, int vert2) const = 0;
    virtual int weight_of_connection (int vert1, int vert2) const = 0;
    virtual void add_connection (int vert1, int vert2, int weight) = 0;
    virtual void output () const = 0;
    virtual bool is_cyclic_rec (int curr_vertex, bool* visited, bool *recStack) const = 0;
    virtual void dfs_for_topological (int vertex, std::vector<bool>& visited, std::vector<int>& result) const = 0;
    virtual int weight_of_graph() const = 0;

};

#endif //NEWVERSION_GRAPH_H

