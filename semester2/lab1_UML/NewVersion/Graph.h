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
    /**
     * @brief Simple getter for amount of vertices
     *
     * @return amount of vertices
     */
    int get_vertex_count () const {
        return vertex_count;
    }

    /**
     * @brief Simple getter to get if graph oriented
     *
     * @return is graph oriented
     */
    bool get_is_oriented () const {
        return is_oriented;
    }

    /**
     * @brief Simple getter to get max possible amount of vertices in graph
     *
     * @return maximal amount of vertices
     */
    static int get_max_vert_count () {
        return MAX_VERTEX_COUNT;
    }
    /**
     * @brief Change orientation of graph
     *
     * If orientation changes from true to false all one way connections are mirrored.
     *
     * @param oriented new orientation of graph
     */
    virtual void change_oriented(bool oriented) = 0;
    /**
     * @brief Shows if specified vertices are connected
     *
     * @param vert1 first vertex to check
     * @param vert2 second vertex to check
     *
     * @return Return true if specified vertex are connected and false if they not.
     */
    virtual bool is_connected (int vert1, int vert2) const = 0;
    /**
     * @brief Shows weight of connection for two specified vertices
     *
     * @param vert1 first vertex to check
     * @param vert2 second vertex to check
     *
     * @return weight of connection between vert1 and vert2
     */
    virtual int weight_of_connection (int vert1, int vert2) const = 0;
    /**
     * @brief Adding connection between two specified vertices.
     *
     * If graph not oriented connection will be established in both ways.
     *
     * @param vert1 first vertex for connection
     * @param vert2 second vertex for connection
     * @param weight weight of connection, 1 if not specified.
     */
    virtual void add_connection (int vert1, int vert2, int weight) = 0;
    /**
     * @brief Output of the graph.
     */
    virtual void output () const = 0;
    /**
     * @brief Recursive part from check is cyclic
     *
     * @param curr_vertex vertex that we are checking in current step
     * @param visited array of flags that shows which vertices already visited and checked
     * @param recStack array that shows if vertex occurs twice
     *
     * @return true if curr_vertex lays in cycle and false if not
     */
    virtual bool is_cyclic_rec (int curr_vertex, bool* visited, bool *recStack) const = 0;
    /**
     * @brief recursive step for topological sort
     *
     * @param vertex current vertex that we want add to result sort
     * @param visited array that shows which vertices were already visited
     * @param result result of topological sort
     */
    virtual void dfs_for_topological (int vertex, std::vector<bool>& visited, std::vector<int>& result) const = 0;
    /**
     * @brief Calculate weight of whole graph.
     *
     * Weight of graph means sum of weight of all connections.
     *
     * @return weight of graph.
     */
    virtual int weight_of_graph() const = 0;
};

#endif //NEWVERSION_GRAPH_H

