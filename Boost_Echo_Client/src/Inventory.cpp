//
// Created by yuval on 07/01/2020.
//

#include "Inventory.h"

Inventory::Inventory(): genre_Book_Map(std::unordered_map<std::string ,std::list<std::string >>()), book_Loaner_Map(std::unordered_map<std::string,std::string> ()), book_Borrower_Map(std::unordered_map<std::string,std::string> ()){}

void Inventory::AddGenre(std::string genre)
{
    genre_Book_Map.insert(std::make_pair(genre,std::list<std::string>()));
}
void Inventory:: AddBook(std::string genre,std::string book_Name)
{
    if(genre_Book_Map.find(genre)==genre_Book_Map.end())
    {
        this->AddGenre(genre);
    }
    std::list<std::string> l=genre_Book_Map[genre];
    l.insert(l.end(),book_Name);
}
void Inventory::AddBorrowedBook(std::string genre,std::string book_Name,std::string loaner_Name)
{
    this->AddBook(genre,book_Name);
    book_Loaner_Map.insert(std::make_pair(book_Name,loaner_Name));

}
void Inventory::lendBook(std::string genre,std::string book_Name,std::string borrower_Name)
{
    this->Delete_Book(genre,book_Name);
    book_Borrower_Map.insert(std::make_pair(book_Name,borrower_Name));
}
bool Inventory::Contains(std::string genre,std::string book_Name)
{
    std::list<std::string> l=genre_Book_Map[genre];
    for(auto book:l)
    {
        if(book==book_Name)
            return true;
    }
    return false;
}

void Inventory:: Delete_Book(std::string genre,std::string book)
{
    std::list<std::string> l=genre_Book_Map[genre];
    l.remove(book);
}