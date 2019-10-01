#ifndef LAB1_GRAPH_TREE_CHARACTERS_H
#define LAB1_GRAPH_TREE_CHARACTERS_H

#include <iostream>
#include<vector>
#include<string>
#include <cassert>
using namespace std;

#include "books.h"


class Characters {
private:
    vector<string> names;
    vector<string> books;
    vector<string> types;
public:
    Characters() = default;
    Characters (vector<string> new_names, vector<string> new_books, vector<string> new_types)
        :names(new_names), books(new_books), types(new_types) {
        assert(new_names.size() == new_books.size() && new_names.size() == new_types.size());
    }

    vector<string> get_names () const {
        return names;
    }
    vector<string> get_books () const {
        return books;
    }
    vector<string> get_types () const {
        return types;
    }

    void add_new_role (string name, string book, string type) {
        names.push_back(name);
        books.push_back(book);
        types.push_back(type);
    }

    void remove_by_book (string book) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i] == book) {
                books.erase(books.begin()+i);
                names.erase(names.begin()+i);
                types.erase(types.begin()+i);
            }
        }
    }
    void remove_by_name (string name) {
        for (int i = 0; i < names.size(); i++) {
            if (names[i] == name) {
                books.erase(books.begin()+i);
                names.erase(names.begin()+i);
                types.erase(types.begin()+i);
            }
        }
    }
    void remove_by_type (string type) {
            for (int i = 0; i < types.size(); i++) {
                if (types[i] == type) {
                    books.erase(books.begin()+i);
                    names.erase(names.begin()+i);
                    types.erase(types.begin()+i);
                }
            }
    };

    void change_book (string change_this, string change_to_this) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i] == change_this) {
                books[i] = change_to_this;
            }
        }
    }
    void change_name (string change_this, string change_to_this) {
        for (int i = 0; i < names.size(); i++) {
            if (names[i] == change_this) {
                names[i] = change_to_this;
            }
        }
    }
    void change_type (string change_this_book, string change_to_this){
        for (int i = 0; i < books.size(); i++) {
            if (change_this_book == books[i]) {
                types[i] = change_to_this;
            }
        }
    }
};


int save_to_file_ch (vector<Characters> characters) {
    ofstream save;
    save.open("save_file_ch.txt", ios::ate);
    for (auto item : characters) {
        for (auto item_name : item.get_names()) {
            save << item_name << '%';
        }
        save << endl;
        for (auto item_book : item.get_books()) {
            save << item_book << '%';
        }
        save << endl;
        for (auto item_type : item.get_types()) {
            save << item_type << '%';
        }
        save << endl;
        save << "^"<<endl;
    }
    save<<"^%"<<endl;
    return save.tellp();
}

vector<Characters> read_from_file_ch (int pos) {
    ifstream save;
    save.open("save_file_ch.txt");
    string line, element = "", check = "^";
    vector<Characters> result;

    save.seekg(pos);
    while (check != "^%") {
        vector<string> names,types,books;
        result.resize(result.size()+1);
        getline(save, line);
        for (auto item : line) {
            if (item == '%') {
                names.push_back(element);
                element = "";
            } else { element += item; }
        }

        getline(save, line);
        for (auto item : line) {
            if (item == '%') {
                books.resize(books.size() + 1);
                books[books.size() - 1] = element;
                element = "";
            } else { element += item; }
        }

        getline(save, line);
        for (auto item : line) {
            if (item == '%') {
                types.push_back(element);
                element = "";
            } else { element += item; }
        }
        for (int i = 0; i < names.size(); i++) {
            result[result.size()-1].add_new_role(names[i], books[i], types[i]);
        }
        names.clear(); books.clear(); types.clear();
        getline(save, check);
    }
    return result;
}
#endif //LAB1_GRAPH_TREE_CHARACTERS_H
