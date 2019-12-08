#define CATCH_CONFIG_MAIN
#include<vector>
#include "Catch2-master/single_include/catch2/catch.hpp"
#include"tm_functions.h"
#include"books.h"

//#include"chatacters.h"

using namespace std;

TEST_CASE("Changes methods work", "[Book]") {

    tm time = random_time();
    Book book("any_name", std::vector<string>{"author_1", "author_2"},time, 123, "anotation_file_x");

    REQUIRE( book.get_name() == "any_name");
    REQUIRE( book.get_date() == time);
    REQUIRE( book.get_page_amount() == 123);
    REQUIRE( book.get_authors()[0] == "author_1");
    REQUIRE( book.get_authors()[1] == "author_2");

    SECTION( "change name" ) {
        book.change_name("any_new_name");

        REQUIRE( book.get_name() == "any_new_name");
    }
    SECTION( "change time" ) {
        tm new_time = random_time();
        book.change_release_date(new_time);

        REQUIRE( book.get_date() == new_time);
    }
    SECTION( "change page amount" ) {
        book.change_pages(6436);

        REQUIRE( book.get_page_amount() == 6436);
    }
    SECTION( "add new author" ) {
        book.add_author("author_3");

        REQUIRE( book.get_authors()[0] == "author_1");
        REQUIRE( book.get_authors()[1] == "author_2");
        REQUIRE( book.get_authors()[2] == "author_3");
    }
    SECTION( "add new author" ) {
        book.add_author("author_2");

        REQUIRE( book.get_authors()[0] == "author_1");
        REQUIRE( book.get_authors()[1] == "author_2");
        REQUIRE( book.get_authors().size() == 2);
    }
}


TEST_CASE("Check searches", "[Book]") {
    tm time = random_time();
    Book book1("any_name1", std::vector<string>{"author_1", "author_2"},time, 123, "anotation_file_1");
    Book book2("any_name2", std::vector<string>{"author_1", "author_3"},time, 11, "anotation_file_x");
    Book book3("gfdfg", std::vector<string>{"afgbbb", "dfbdfb"},time, 7364, "anotation_file_x");
    Book book4("very intresting", std::vector<string>{"no name"},time, 233, "anotation_file_x");
    Book book5("amazing book", std::vector<string>{"author_3"},time, 234, "anotation_file_x");
    vector<Book> books = {book1, book2, book3, book4, book5};

    SECTION( "search name" ) {
        REQUIRE( search_by_name(books, "name") == std::vector<Book>{book1,book2});
        REQUIRE( search_by_name(books, "book") == std::vector<Book>{book5});
        REQUIRE( search_by_name(books, "ing") == std::vector<Book>{book4,book5});
        REQUIRE( search_by_name(books, "what").empty());
    }
    SECTION( "search author" ) {
        REQUIRE( search_by_author(books, "author_1") == std::vector<Book>{book1,book2});
        REQUIRE( search_by_author(books, "no name") == std::vector<Book>{book4});
        REQUIRE( search_by_author(books, "name").empty());
        REQUIRE( search_by_author(books, "what").empty());
    }
    SECTION( "search time interval" ) {
        tm second_time = random_time();
        while (second_time < time ) {second_time = random_time();}
        REQUIRE( search_by_release_interval(books, time, second_time) == books);
        REQUIRE( search_by_release_interval(books, second_time, second_time).empty());
        REQUIRE( search_by_release_interval(books, time, time) == books);
    }
    SECTION( "search pages interval" ) {
        REQUIRE( search_by_pages_interval(books, 0, 100) == std::vector<Book>{book2});
        REQUIRE( search_by_pages_interval(books, 100, 100).empty());
        REQUIRE( search_by_pages_interval(books, 11,7364) == books);
        REQUIRE( search_by_pages_interval(books, 233, 500) == std::vector<Book>{book4,book5});
    }
}