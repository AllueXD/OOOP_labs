#ifndef NEWVERSION_ADDITIONALBORUVKA_H
#define NEWVERSION_ADDITIONALBORUVKA_H

#include <iostream>
#include <vector>
#include <cassert>



class boruvka_subset {
    std::vector<int> vertexes;

public:
    /**
     * @brief Simple getter for vertex by index
     *
     * @return vertex at index
     */
    int get_vertex(int index) const {
        return vertexes[index];
    }

    /**
     * @brief Simple getter for size of vector of vertices
     *
     * @return size of vector
     */
    int get_size() const {
        return vertexes.size();
    }

    /**
     * @brief Adding new element to vector of vertices
     *
     * Checks if element can be vertex (>=0) and adding to vector if so, else throwing assert
     *
     * @param element vertex number
     *
     */
    void add(int element) {
        assert(element>=0);
        vertexes.push_back(element);
    }

    /**
     * @brief Finding lowest connection from this set to any other
     *
     * @param lows vector with the cheapest connections for every vertex from graph
     * @return pair of two connected vertices
     */
    std::pair<int,int> lowest_in_subset (std::vector<std::pair<int,int>>& lows) {
        int min = lows[vertexes[0]].second;
        std::pair<int,int> vert_with_min = {vertexes[0], lows[vertexes[0]].first};
        for (int i = 1; i < this->get_size(); i++) {
            if (lows[vertexes[i]].second < min) {
                min = lows[vertexes[i]].second;
                vert_with_min = {vertexes[i], lows[vertexes[i]].first};
            }
        }
        return vert_with_min;
    }
};

    /**
     * @brief Finding in which subset lays vertex
     *
     * @param vector with all available subsets
     * @param vert vertex for which we searching subset
     * @param amount_of_component current amount of subsets
     *
     * @return subset index in vector of subsets
     */
int find_subset_by_vert (std::vector<boruvka_subset>& subs, int vert, int amount_of_component) {
    for (int i = 0; i < amount_of_component; i++) {
        for (int j = 0; j < subs[i].get_size(); j++) {
            if (subs[i].get_vertex(j) == vert) { return i; }
        }
    }
}

    /**
     * @brief Union two subsets by vertices
     *
     * Finding index of subset in vector of subsets for first vertex and same for second vertex.
     * Then union this two subsets in one subset with all their vertices.
     * And decrease by one amount of subsets.
     *
     * @param subs current vector of subsets
     * @param vert1 first vertex for union
     * @param vert2 second vertex for union
     * @param amount_of_component current amount of subsets
     *
    */
void union_subsets (std::vector<boruvka_subset>& subs, int vert1, int vert2, int* amount_of_component) {
    int subset_of_vert1, subset_of_vert2;
    subset_of_vert1 = find_subset_by_vert(subs, vert1, *amount_of_component);
    subset_of_vert2 = find_subset_by_vert(subs, vert2, *amount_of_component);
    if (subset_of_vert1 != subset_of_vert2) {
        for (int i = 0; i < subs[subset_of_vert2].get_size(); i++) {
            subs[subset_of_vert1].add(subs[subset_of_vert2].get_vertex(i));
        }
        subs.erase(subs.begin() + subset_of_vert2);
        (*amount_of_component)--;
    }
}

#endif //NEWVERSION_ADDITIONALBORUVKA_H
