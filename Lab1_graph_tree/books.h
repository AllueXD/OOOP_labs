
#ifndef LAB1_GRAPH_TREE_BOOKS_H
#define LAB1_GRAPH_TREE_BOOKS_H

#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
#include<algorithm>
#include<string>
#include <cassert>
#include "tm_functions.h"
#include "characters.h"
#include "alternative_realities.h"

using namespace std;

class Book {
private:
    string name;
    vector<string> authors;
    tm release_date;
    int pages;
    string anotation_file_name;
    vector<Characters> all_characters;
    Additional additional;

public:
    Book () = default;
    Book (const string& new_name, const vector<string>& new_authors, const tm& new_release, const int new_pages, const string& anotation = "")
        : name(new_name), authors(new_authors), release_date(new_release), anotation_file_name(anotation), additional(){
        assert(new_pages > 0);
        pages = new_pages;
    }

    string get_name () const {
        return name;
    }
    vector<Characters> get_characters () const {
        return all_characters;
    }
    tm get_date () const {
        return release_date;
    }
    int get_page_amount () const {
        return pages;
    }
    vector<string> get_authors () const {
        return authors;
    }
    string get_anotation () const {
        return anotation_file_name;
    }
    void read_anotation() {
        ifstream anotation;
        string line;
        anotation.open(anotation_file_name);
        if (anotation.is_open()){
            while (getline (anotation, line)) {
                cout<<line<<endl;
            }
            anotation.close();
        }
        else {cout<<"Can't find any anotation to this book";}
    }
    Additional get_additional_info () {
        return additional;
    }

    void change_name (const string& new_name) {
        assert(!new_name.empty());
        name = new_name;
    }

    void add_author (const string& new_author) {
        auto find_pos = find(authors.begin(), authors.end(), new_author);
        if (find_pos == authors.end()) {
            authors.push_back(new_author);
        }
        else {cout<<"This author already in the author's list"<<endl;}
    }
    void remove_author (const string& author_to_delete) {
        auto find_pos = find (authors.begin(), authors.end(), author_to_delete);
        authors.erase(find_pos);
    }

    void add_character (const Characters& new_character) {
        all_characters.push_back(new_character);
    }
    /*void remove_character (const Characters& character_to_delete) {
        auto find_pos = find (all_characters.begin(), all_characters.end(), character_to_delete);
        all_characters.erase(find_pos);
    }*/

    void change_pages (int new_amount) {
        assert (new_amount > 0);
        pages = new_amount;
    }
    void change_release_date(tm new_date) {
        release_date = new_date;
    }

    void change_anotation (const string& new_anot) {
        anotation_file_name = new_anot;
    }
    void add_to_anotation (const string& add_this) {
        ofstream anotation;
        anotation.open(anotation_file_name, ios::ate);
        anotation << add_this << endl;
        anotation.close();
    }
    void clear_anotation () {
        ofstream anotation;
        anotation.open(anotation_file_name, ios::trunc);
        anotation.close();
    }

};

bool operator == (Book left, Book right) {
    return (left.get_name() == right.get_name());
}

void save_to_file (vector<Book> books) {
    ofstream save;
    save.open("save_file.txt", ios::ate);
    for (auto item : books) {
        save << item.get_name() << endl;
        for (auto item_author: item.get_authors()) {
            save << item_author << '%';
        }
        save << endl;
        save << item.get_date() << endl;
        save << item.get_page_amount() << endl;
        save << item.get_anotation() << endl;
        save << save_to_file_ch(item.get_characters()) << endl;
    }
    save.close();
}
vector<Book> read_from_file () {
    ifstream save;
    save.open("save_file.txt");
    string line, element;
    vector<Book> result;

    int pos = 0;
    while (!save.eof()) {
        result.resize(result.size()+1);
        element = "";
        getline(save, line);
        result[result.size()-1].change_name(line);

        getline(save, line);
        for (auto item : line) {
            if (item == '%') {
                result[result.size()-1].add_author(element);
                element = "";
            } else { element += item; }
        }

        getline(save, line);
        result[result.size()-1].change_release_date(stotm(line));

        getline(save, line);
        result[result.size()-1].change_pages(stoi(line));

        getline(save, line);
        result[result.size()-1].change_anotation(line);

        vector<Characters> characters;
        characters = read_from_file_ch(pos);

        for (auto item : characters) {result[result.size()-1].add_character(item);}

        getline(save, line);
        pos = stoi(line);
    }
    save.close();
    return result;
}

vector<vector<Book>> series(const vector<Book>& books) {
    vector<vector<Book>> result;
    vector<Book> row;
    vector<string> used;

    for (auto &item_book : books) {
        if (std::find(used.begin(), used.end(), item_book.get_name()) != used.end()) {break;}
        for (int i = 0; i < item_book.get_characters().size(); i++) {
            auto t = std::find(item_book.get_characters()[i].get_books().begin(), item_book.get_characters()[i].get_books().end(), item_book.get_name());
            if (*t != "episodic") {
               for (int j = 0; j < item_book.get_characters()[i].get_books().size(); j++) {
                   if (item_book.get_characters()[i].get_types()[j] != "episodic" && item_book.get_characters()[i].get_types().begin()+j != t) {
                       row.push_back(item_book);
                       used.push_back(item_book.get_characters()[i].get_books()[j]);
                   }
               }
               result.push_back(row);
               row.clear();
               break;
            }
        }
    }

    for (auto item : result) {
        sort(item.begin(),item.end(), [&](const Book& left, const Book& right)
                                {return left.get_date() < right.get_date();});
    }
    return result;
}

vector<Book> search_by_name (const vector<Book>& books, const string& subname) {
    vector<Book> result;

    for (auto item : books) {
        if (item.get_name().find(subname) != string::npos){
            result.push_back(item);
        }
    }
    return result;
}
vector<Book> search_by_author (const vector<Book> books, const string& author) {
    vector<Book> result;

    for (auto item : books) {
        for (auto item_authors: item.get_authors()) {
            if (item_authors == author) {result.push_back(item);}
        }
    }
    return result;
}
vector<Book> search_by_release_interval (const vector<Book>& books, const tm& left, const tm& right) {
    vector<Book> result;

    for (auto item : books) {
        if (item.get_date()>=left && item.get_date()<=right) {result.push_back(item);}
    }
    return result;
}
vector<Book> search_by_pages_interval (const vector<Book>& books, int left, int right) {
    vector<Book> result;

    for (auto item : books) {
        if (item.get_page_amount() >= left && item.get_page_amount() <= right) {result.push_back(item);}
    }
    return result;
}
vector<Book> search_by_characters (const vector<Book>& books, string character_name) {
    vector<Book> result;

    for(auto item : books) {
        for (auto item_characters : item.get_characters()) {
            for (int i = 0; i < item_characters.get_names().size(); i++) {
                if (item_characters.get_names()[i] == character_name
                && item_characters.get_books()[i] == item.get_name()) {
                    result.push_back(item);
                }
            }
        }
    }

    return result;
}

vector<Book> search_by_film_base (const vector<Book>& books, string film_base) {
    vector<Book> result;
    for (auto item : books) {
        if (search(item.get_additional_info().get_film_base().begin(), item.get_additional_info().get_film_base().end(),
                film_base.begin(), film_base.end()) != item.get_additional_info().get_film_base().end()){
            result.push_back(item);
        }
        return result;
    }
}
vector<Book> search_book_by_film (const vector<Book>& books, string film) {
    vector<Book> result;
    for (auto item : books) {
        if (search(item.get_additional_info().get_film_by_book().begin(), item.get_additional_info().get_film_by_book().end(),
                   film.begin(), film.end()) != item.get_additional_info().get_film_by_book().end()){
            result.push_back(item);
        }
        return result;
    }
}

#endif //LAB1_GRAPH_TREE_BOOKS_H
