//
// Created by yuval on 07/01/2020.
//

#include "Database.h"
Database* Database::instance=0;
Database *Database::getInstance() {
    if(Database::instance==0)
    {
        Database::instance=new Database();
    }
    return Database::instance;
}
Database::Database(): genre_Book_Map(std::unordered_map<std::string ,std::list<std::string >>()), book_Loaner_Map(std::unordered_map<std::string,std::string> ()), genre_SubId_map(std::unordered_map<std::string,std::string> ()){}

void Database::addGenre(std::string genre,std::string subId)
{
    genre_Book_Map.insert(std::make_pair(genre,std::list<std::string>()));
    genre_SubId_map.insert(std::make_pair(subId,genre));
}
void Database:: addBook(std::string genre, std::string book_Name)
{
    if(genre_Book_Map.find(genre)==genre_Book_Map.end())
    {
        this->addGenre(genre);
    }
    std::list<std::string> l=genre_Book_Map[genre];
    l.insert(l.end(),book_Name);
}
void Database::addBorrowedBook(std::string genre, std::string book_Name, std::string loaner_Name)
{
    this->addBook(genre, book_Name);
    book_Loaner_Map.insert(std::make_pair(book_Name,loaner_Name));

}
void Database::lendBook(std::string genre, std::string book_Name, std::string borrower_Name)
{
    this->delete_Book(genre, book_Name);
}
bool Database::contains(std::string genre, std::string book_Name)
{
    std::list<std::string> l=genre_Book_Map[genre];
    for(auto book:l)
    {
        if(book==book_Name)
            return true;
    }
    return false;
}


void Database:: delete_Book(std::string genre, std::string book)
{
    std::list<std::string> l=genre_Book_Map[genre];
    l.remove(book);
}

bool Database::wantedToBorrow(std::string book) {
    for(auto bookname:want_TO_Borrow) {
        if (bookname == book)
            return true;
    }
    return false;
}

void Database::setName(std::string name) {
    this->name=name;
}

std::string Database::getName() {
    return name;
}

void Database::addReciept(std::string recieptId, Command command) {
    reciept_Enum_map.insert(std::make_pair(recieptId,command));
}

void Database::addToBorrowList(std::string book) {
    want_TO_Borrow.push_back(book);
}

std::string Database::getLoanerName(std::string book) {
    return std::__cxx11::string();
}


