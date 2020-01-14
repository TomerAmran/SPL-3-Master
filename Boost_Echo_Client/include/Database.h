//
// Created by yuval on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_DATABASE_H
#define BOOST_ECHO_CLIENT_DATABASE_H
#include <list>
#include <unordered_map>
#include <string>
#include <mutex>
#include "StompFrame.h"

class Database {

public:
    Database(Database const &)= delete;
    ~Database();
    Database& operator=(const Database& database)= delete;
    Database& operator=(const Database&& database)= delete;
    Database(Database&& database)= delete;
    static Database* getInstance();
    void addGenre(std::string genre, std::string subId);
    void addBook(std::string genre, std::string book_Name);
    void addBorrowedBook(std::string genre, std::string book_Name, std::string loaner_Name);
    void lendBook(std::string genre, std::string book_Name);
    bool contains(std::string genre, std::string book_Name);
    bool wantedToBorrow(std::string book);
    void setName(std::string name);
    std::string getName();
    void addReciept(std:: string recieptId,StompFrame* frame);
    void addToBorrowList(std::string);
    std::string getLoanerName(std::string book);
    void deleteBook(std::string genre, std::string book);
    StompFrame* getReciept(std::string id);
    void removeReciept(std::string id);
    std::list<std::string> & getBooksByGenre(std::string genre);
    std::string getSubid(std::string genre);


private:
    Database();
    static Database* instance;
    std::unordered_map<std::string,std::list<std::string>> genre_Book_Map;
    std::unordered_map<std::string,std::string> book_Loaner_Map;
    std::unordered_map<std::string,std::string> genre_SubId_map;
    std::list<std::string > want_TO_Borrow;
    std::string name;
    std::unordered_map<std::string,StompFrame*> reciept_Frame_map;
    std:: mutex genre_book_lock;
    std:: mutex want_to_borrow_lock;
    std::mutex reciept_frame_lock;
    void addGenre(std::string genre);
};

#endif

