#ifndef LAB1_MUTUALFUNCTIONS_H
#define LAB1_MUTUALFUNCTIONS_H

#include <iostream>
#include <vector>

using namespace std;

const int max_vert_count = 500;

bool compare_weight (std::pair<int,int> left, std::pair<int,int> right) {
    return left.second<right.second;
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


#endif //LAB1_MUTUALFUNCTIONS_H
