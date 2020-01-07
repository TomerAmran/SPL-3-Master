//
// Created by yuval on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_INVENTORY_H
#define BOOST_ECHO_CLIENT_INVENTORY_H
#include <list>
#include <unordered_map>
#include <string>
class Inventory {

public:
    Inventory();
    void AddGenre(std::string genre);
    void AddBook(std::string genre,std::string book_Name);
    void AddBorrowedBook(std::string genre,std::string book_Name,std::string loaner_Name);
    void lendBook(std::string genre,std::string book_Name,std::string loaner_Name);
    bool Contains(std::string genre,std::string book_Name);
private:
    std::unordered_map<std::string,std::list<std::string>> genre_Book_Map;
    std::unordered_map<std::string,std::string> book_Borrower_Map;
    std::unordered_map<std::string,std::string> book_Loaner_Map;
    void Delete_Book(std::string genre,std::string book);



};

#endif

