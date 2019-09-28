
#ifndef LAB1_GRAPH_TREE_BOOKS_H
#define LAB1_GRAPH_TREE_BOOKS_H

#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
#include<algorithm>
#include<string>
#include <cassert>
#include"tm_functions.h"
#include"characters.h"


class Book {
private:
    string name;
    vector<string> authors;
    tm release_date;
    int pages;
    string anotation_file_name;
    vector<Characters> all_characters;

public:
    Book () = default;
    Book (const string& new_name, const vector<string>& new_authors, const tm& new_release, const int new_pages, const string& anotation = "")
        : name(new_name), authors(new_authors), release_date(new_release), anotation_file_name(anotation){
        assert(new_pages > 0);
        pages = new_pages;
    }

    string& get_name () const {
        return name;
    }
    vector<Characters>& get_characters () const {
        return all_characters;
    }
    tm& get_date () const {
        return release_date;
    }
    int get_page_amount () const {
        return pages;
    }
    vector<string> get_authors () const {
        return authors;
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

    void change_name (const string& new_name) {
        name = new_name;
    }

    void add_author (const string& new_author) {
        auto find_pos = find(authors.begin(), authors.end(), new_author);
        if (find_pos != authors.end()) {
            authors.push_back(new_author);
        }
        else {cout<<"This author already in the author's list"<<endl;}
    }
    void remove_author (const string& author_to_delete) {
        auto find_pos = find (authors.begin(), authors.end(), author_to_delete);
        authors.erase(find_pos);
    }

    void add_character (const Characters& new_character) {
        auto find_pos = find(all_characters.begin(), all_characters.end(), new_character);
        if (find_pos != all_characters.end()) {
            all_characters.push_back(new_character);
        }
        else {cout<<"This character already in the author's list"<<endl;}
    }
    void remove_character (const Characters& character_to_delete) {
        auto find_pos = find (all_characters.begin(), all_characters.end(), character_to_delete);
        all_characters.erase(find_pos);
    }

    void change_pages (int new_amount) {
        assert (new_amount > 0, "pages amount can't be lower then 0");
        pages = new_amount;
    }
    void change_release_date(tm& new_date) {
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
        ofstream anotation.open(anotation_file_name, ios::trunc);
        anotation.close();
    }

};

void save_to_file (vector<Book> books) {
    ofstream save.open("save_file.txt", ios::ate);
    for (auto item : books) {
        save << name << endl;
        for (auto item : authors) {
            save << item << '%';
        }
        save << endl;
        save << release_date << endl;
        save << pages << endl;
        save << anotation_file_name << endl;
        save << save_to_file_ch(item.get_characters()) << endl;
    }
    save.close();
}
vector<Book> read_from_file () {
    ifstream save.open("save_file.txt");
    string line, element;
    vector<Book> result;

    int pos = 0;
    while (!save.EOF()) {
        result.resize(result.size()+1);
        result[result.size()-1]();
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
        result[result.size()-1].change_release_date(stotm(line))

        getline(save, line);
        result[result.size()-1].change_pages(stoi(line));

        getline(save, line);
        result[result.size()-1].change_anotation(line);

        vector<Characters> characters;
        do {
            characters.resize(characters.size() + 1);
            characters[characters.size() - 1].read_from_file(pos);
            pos = pos + 3;
        } while (characters[characters.size() - 1].read_from_file(pos - 3));
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
            if (item_book.get_characters()[i].get_types() != "episodic") {
               for (int j = 0; j < item_book.get_characters()[i].get_books().size(); j++) {
                   if (item_book.get_characters()[i].get_types()[j] != "episodic") {
                       row.push_back(item.get_characters()[i].get_books()[j]);
                       used.push_back(item.get_characters()[i].get_books()[j].get_name);
                   }
               }
               result.push_back(row);
               row.erase();
               break;
            }
        }
    }

    for (auto item : result) {
        sort(item.begin(),item.end(), [](const Book& left, const Book& right)
                                {return left.get_date() < right.get_date();})
    }
    return result;
}

vector<Book> search_by_name (const vector<Book>& books, const string& subname) {
    vector<Book> result;

    for (auto item : books) {
        if (search(item.get_name().begin(), item.get_name().end(), subname.begin(), subname.end()) != item.get_name().end()){
            result.push_back(item);
        }
        return result;
    }
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

#endif //LAB1_GRAPH_TREE_BOOKS_H
