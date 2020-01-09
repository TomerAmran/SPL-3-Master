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
Database::Database(): genre_Book_Map(std::unordered_map<std::string ,std::list<std::string >>()),
                                        book_Loaner_Map(std::unordered_map<std::string,std::string> ()),
                                        genre_SubId_map(std::unordered_map<std::string,std::string> ()),
                                        want_TO_Borrow(std::list<std::string>()),name(""),
                                        reciept_Frame_map(std::unordered_map<std::string,StompFrame*>()){}

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
void Database::lendBook(std::string genre, std::string book_Name)
{
    this->deleteBook(genre, book_Name);
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


void Database:: deleteBook(std::string genre, std::string book)
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

void Database::addReciept(std::string recieptId, StompFrame* frame) {
    reciept_Frame_map.insert(std::make_pair(recieptId, frame));
}

void Database::addToBorrowList(std::string book) {
    want_TO_Borrow.push_back(book);
}

std::string Database::getLoanerName(std::string book) {
    return book_Loaner_Map[book];
}

StompFrame* Database::getReciept(std::string id) {
    return reciept_Frame_map[id];
}

void Database::removeReciept(std::string id) {
   StompFrame* frame= reciept_Frame_map[id];
    delete frame;
    frame= nullptr;
    reciept_Frame_map.erase(id);
}
std::list<std::string> & Database::getBooksByGenre(std::string genre) {
    return genre_Book_Map[genre];
}

void Database::addGenre(std::string genre) {
    genre_Book_Map.insert(std::make_pair(genre,std::list<std::string>()));
}




