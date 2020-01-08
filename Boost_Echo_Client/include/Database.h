//
// Created by yuval on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_DATABASE_H
#define BOOST_ECHO_CLIENT_DATABASE_H
#include <list>
#include <unordered_map>
#include <string>
#include "StompFrame.h"

class Database {

public:
    static Database* getInstance();
    void addGenre(std::string genre, std::string subId);
    void addBook(std::string genre, std::string book_Name);
    void addBorrowedBook(std::string genre, std::string book_Name, std::string loaner_Name);
    void lendBook(std::string genre,std::string book_Name,std::string loaner_Name);
    bool contains(std::string genre, std::string book_Name);
    bool wantedToBorrow(std::string book);
    void setName(std::string name);
    std::string getName();
    void addReciept(std:: string recieptId,Command command);
    void addToBorrowList(std::string);
    std::string getLoanerName(std::string book);
    void delete_Book(std::string genre, std::string book);


private:
    Database();
    static Database* instance;
    std::unordered_map<std::string,std::list<std::string>> genre_Book_Map;
    std::unordered_map<std::string,std::string> book_Loaner_Map;
    std::unordered_map<std::string,std::string> genre_SubId_map;
    std::list<std::string > want_TO_Borrow;
    std::string name;
    std::unordered_map<std::string,Command> reciept_Enum_map;




};

#endif

