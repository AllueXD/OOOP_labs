#ifndef LAB1_GRAPH_TREE_ALTERNATIVE_REALITIES_H
#define LAB1_GRAPH_TREE_ALTERNATIVE_REALITIES_H

#include<iostream>
#include<string>

using namespace std;

class Additional {
private:
    bool based_on_film;
    string film_base;
    bool unreleased;
    bool base_for_film;
    string film_by_book;
public:
    explicit Additional(const string& base = "", const string& film = "", bool is_unreleased = false)
    : film_base(base), film_by_book(film), unreleased(is_unreleased){
        if (base.empty()) {based_on_film = false;}
        if (film.empty()) {base_for_film = false;}
    }
    bool is_based_on_film() const {
        return based_on_film;
    }
    string get_film_base() const {
        if (!based_on_film) {cout<<"this book isn't based on films"<<endl;}
        return film_base;
    }
    bool is_base_for_film() const {
        return base_for_film;
    }
    string get_film_by_book() const {
        if (!base_for_film) {cout<<"this book isn't based on films"<<endl;}
        return film_by_book;
    }
    bool is_unreleased() const {
        return unreleased;
    }

    void add_film_base (const string& film) {
        based_on_film = true;
        film_base = film;
    }

    void add_film_by_book (const string& film) {
        base_for_film = true;
        film_by_book = film;
    }

    void change_unreleased (bool is_released) {
        unreleased = !is_released;
    }

    void remove_film_base () {
        based_on_film = false;
        film_base = "";
    }

    void remove_film_by_book () {
        base_for_film = false;
        film_by_book = "";
    }

};

#endif //LAB1_GRAPH_TREE_ALTERNATIVE_REALITIES_H
