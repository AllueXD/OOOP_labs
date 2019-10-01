#ifndef LAB1_GRAPH_TREE_TREE_H
#define LAB1_GRAPH_TREE_TREE_H

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "tm_functions.h"
#include <ctime>
#include <cassert>

using namespace std;

template<typename T>
class TreeNode {
private:
    T data;
    vector<TreeNode*> child;
    TreeNode* parent;
public:
    explicit TreeNode(T f_data)
    : data(f_data), parent(nullptr) {}

    T get_data () const {
        return data;
    }
    TreeNode* get_child(int index) const {
        return child.at(index);
    }
    TreeNode* get_parent () const {
        return parent;
    }
    void add_child (TreeNode* new_child) {
        child.push_back(new_child);
    }
    void remove_child (TreeNode* child_to_remove) {
        for (int i = 0; i < child.size(); i++) {
            if (child[i] == child_to_remove) {
                child.erase(child.begin()+i);
            }
        }
    }
    void change_parent (TreeNode* new_parent) {
        parent = new_parent;
    }
    void change_data (T new_data) {
        data = new_data;
    }
    int get_child_amount() const {
        return child.size();
    }
    bool childs_empty () const {
        return child.empty();
    }
};

template <typename T>
TreeNode<T>* insert_by_index (T insert_value, int input_index, TreeNode<T>* root) {
    auto input_node = new TreeNode<T>(insert_value);
    queue<pair<TreeNode<T>*, int>> q;
    int curr_index = 0;

    if (root == nullptr) { return input_node;}

    q.push(make_pair(root, curr_index));
    curr_index++;
    while (!q.empty()) {
        pair<TreeNode<T>*,int> curr_node = q.front();
        q.pop();
        if (curr_node.second == input_index) {
            input_node->change_parent(curr_node.first);
            curr_node.first->add_child(input_node);
        }
        for (int i = 0; i < (curr_node.first)->get_child_amount(); i++) {
            q.push(make_pair(curr_node.first->get_child()[i], curr_index));
            curr_index++;
        }
    }
    return root;
}

template<typename T>
void insert_by_path (T insert_value, vector<int>& path, TreeNode<T>* root) {
    auto input_node = new TreeNode<T>(insert_value);
    TreeNode<T>* input_here = root;

    for (int i = 1; i < path.size(); i++) {
        input_here = input_here->get_child(path[i]);
    }

    input_node->change_parent(input_here);
    input_here->add_child(input_node);
}

template<typename T>
void interactive_output (TreeNode<T>* root) {
    TreeNode<T>* curr_node = root;
    int next;
    if (curr_node->get_parent() != nullptr) {
        cout<<"Parent: "<<(curr_node->get_parent())->get_data()<<"[0]"<<endl;
    }
    cout<<"Current node: "<<curr_node->get_data()<<endl;
    if (!curr_node->childs_empty()) {
        cout<<"Childs: ";
        for (int i = 0; i < curr_node->get_child_amount(); i++) {cout<< curr_node->get_child(i)->get_data()<<'['<<i+1<<"] ";}
        cout<<endl;
    }
    cout<<"Enter index of node to show"<<endl;
    cout<<"(for exit enter -1)"<<endl;
    cin>>next;
    if (next == -1) {return;}
    if (next == 0) {interactive_output(curr_node->get_parent());}
    else {interactive_output(curr_node->get_child(next-1));}
}

template<typename T>
void pre_output (TreeNode<T>* root) {
    if (root != nullptr) {
        cout << root->get_data() << ' ';
        for (int i = 0; i < root->get_child_amount(); i++) { pre_output(root->get_child(i)); }
    }
}

template<typename T>
void delete_by_value (T deleting_value, TreeNode<T>* root) {
    for (int i = 0; i < root->get_child_amount(); i++) {
        delete_by_value(deleting_value, root->get_child(i));
    }
    if (root->get_data() == deleting_value && root->get_parent() != nullptr) {
        for (int i = 0; i < root->get_child_amount(); i++) {
            (root->get_parent())->add_child(root->get_child(i));
        }
        for (int i = 0; i < (root->get_parent())->get_child_amount(); i++) {
            if ((root->get_parent())->get_child(i) == root) {
                (root->get_parent())->remove_child(root);
                //get_child().erase((root->get_parent())->get_child().begin()+i);
            }
        }
        delete root;
    }
}

#endif //LAB1_GRAPH_TREE_TREE_H
