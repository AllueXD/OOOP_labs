#ifndef LAB1_GRAPH_TREE_CHARACTERS_H
#define LAB1_GRAPH_TREE_CHARACTERS_H

#include <iostream>
#include<vector>
#include<string>
#include"books.h"
#include <cassert>
using namespace std;

class Characters {
private:
    vector<string> names;
    vector<Book> books;
    vector<string> types;
public:
    Characters() = default;
    Characters (vector<string> new_names, vector<Book> new_books, vector<string> new_types)
        :names(new_names), books(new_books), types(new_types) {
        assert(new_names.size() == new_books.size() && new_names.size() == new_types.size(),
                "can't create character from this vectors");
    }

    vector<string>& get_names () const {
        return names;
    }
    vector<Book>& get_books () const {
        return books;
    }
    vector<string>& get_types () const {
        return types;
    }

    void add_new_role (string name, Book book, string type) {
        names.push_back(name);
        books.push_back(book);
        types.push_back(type);
    }

    void remove_by_book (Book book) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].get_name() == book.get_name()) {
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

    void change_book (Book change_this, Book change_to_this) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].get_name() == change_this.get_name()) {
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
    void change_type (Book change_this, string change_to_this){
        for (int i = 0; i < books.size(); i++) {
            if (change_this[i].get_name() == books[i].get_name()) {
                types[i] = change_to_this;
            }
        }
    }
};


int save_to_file_ch (vector<Characters> characters) {
    ofstream save.open("save_file_ch.txt", ios::ate);
    for (auto item : characters) {
        for (auto item : names) {
            save << item << '%';
        }
        save << endl;
        for (auto item : books) {
            save << item.get_name() << '%';
        }
        save << endl;
        for (auto item : types) {
            save << item << '%';
        }
        save << endl;
        save << "^"<<endl;
    }
    save<<"^%"<<endl;
    return save.tellp();
}

vector<Characters> read_from_file_ch (int pos) {
    ifstream save.open("save_file_ch.txt");
    string line, element = "", check = "^";
    vector<Characters> result;

    save.seekg(pos);
    while (check != "^%") {
        vector<string> names,types;
        vector<Book> books;
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
                books[books.size() - 1].change_name(element);
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
        result[result.size()-1].add_new_role(names, books, types);
        names.clear(); books.clear(); types.clear();
        getline(save, check);
    }
    return result;
}
#endif //LAB1_GRAPH_TREE_CHARACTERS_H
