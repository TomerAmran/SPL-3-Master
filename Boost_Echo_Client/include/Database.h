//
// Created by yuval on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_DATABASE_H
#define BOOST_ECHO_CLIENT_DATABASE_H
#include <list>
#include <unordered_map>
#include <string>
#include <mutex>
#include <condition_variable>
#include "StompFrame.h"

class Database {

public:
    //singeltone there for no use for copy/move constractors/operator=
    Database(Database const &)= delete;
    ~Database();
    Database& operator=(const Database& database)= delete;
    Database& operator=(const Database&& database)= delete;
    Database(Database&& database)= delete;
    static Database* getInstance();
    // adding  genre when subscribing to it
    void addGenre(std::string genre, std::string subId);
    //adding book to inventory
    void addBook(std::string genre, std::string book_Name);
    //adding the book to inventory and his entry to book loaner map
    void addBorrowedBook(std::string genre, std::string book_Name, std::string loaner_Name);
    // giving away a book
    void lendBook(std::string genre, std::string book_Name);
    // checking if a book is in the inventory
    bool contains(std::string genre, std::string book_Name);
    // checking if i wanted to borrow a book
    bool wantedToBorrow(std::string book);
    //setting user name
    void setName(std::string name);
    //getting user name
    std::string getName();
    // adding reciept id and frame to the map
    void addReciept(std:: string recieptId,StompFrame* frame);
    // adding book to the want to borrow list
    void addToBorrowList(std::string);
    // getting the name of the guy who lended the book
    std::string getLoanerName(std::string book);
    // removing book from inventory
    void deleteBook(std::string genre, std::string book);
    //getting the frame of given reciept
    StompFrame* getReciept(std::string id);
    // removing the map entry of the reciept id
    void removeReciept(std::string id);
    // returning the list of all book in the genre
    std::list<std::string> & getBooksByGenre(std::string genre);
    // gets the subid of a genre
    std::string getSubid(std::string genre);
    std::string getGenreById(std::string subid);
    void unsubscribe(std::string genre);
    std::list<std::string> getGenreList();
    bool canLogOut();


private:
    Database();
    static Database* instance;
    std::unordered_map<std::string,std::list<std::string>> genre_Book_Map;
    std::unordered_map<std::string,std::string> book_Loaner_Map;
    std::unordered_map<std::string,std::string> genre_SubId_map;
    std::list<std::string > want_TO_Borrow;
    std::string name;
    std::unordered_map<std::string,StompFrame*> reciept_Frame_map;
    //to sync the acsses to the genre book map cus both thread may change it
    std:: mutex genre_book_lock;
    //to sync the acsses to the want to borrow list cus both thread may change it
    std:: mutex want_to_borrow_lock;
    //to sync the acsses to the reciept frame map cus both thread may change it
    std::mutex reciept_frame_lock;
    std::mutex genre_subid_lock;
    std::condition_variable cv;
    void addGenre(std::string genre);
};

#endif

