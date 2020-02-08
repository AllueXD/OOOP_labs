//
// Created by yana4bka on 2/7/20.
//

#ifndef NEWVERSION_ADDITIONALBORUVKA_H
#define NEWVERSION_ADDITIONALBORUVKA_H

#include <iostream>
#include <vector>
#include <cassert>

bool compare_weight (std::pair<int,int> left, std::pair<int,int> right) {
    return left.second<right.second;
}

class boruvka_subset {
    std::vector<int> vertexes;

public:
    int get_vertex(int index) const {
        return vertexes[index];
    }

    int get_size() const {
        return vertexes.size();
    }
    void add(int element) {
        assert(element>=0);
        vertexes.push_back(element);
    }

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

int find_subset_by_vert (std::vector<boruvka_subset>& subs, int vert, int amount_of_component) {
    for (int i = 0; i < amount_of_component; i++) {
        for (int j = 0; j < subs[i].get_size(); j++) {
            if (subs[i].get_vertex(j) == vert) { return i; }
        }
    }
}

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
