//
// Created by yuval on 08/01/2020.
//

#include "Protocol.h"

Protocol::Protocol(ConnectionHandler &handler) : handler(handler) {}

bool Protocol::processServer(std::string msg) {
    StompFrame frame = StompFrame();
    frame.parse(msg);
    bool logout=false;
    if (frame.getCommand() == CONNECTED) {
        connected();
    } else if (frame.getCommand() == ERROR) {
        error(frame.getBody());
    } else if (frame.getCommand() == RECEIPT) {
        logout = reciept(frame.getHeaders()["receipt-id"]);
    } else if (frame.getCommand() == MESSAGE) {
        message(frame);
    }
    return logout;
}

std::vector<std::string> Protocol::split_string_to_words_vector(const std::string &string) {
    std::istringstream iss(string);
    std::vector<std::string> words(std::istream_iterator<std::string>{iss},
                                   std::istream_iterator<std::string>());
    return words;
}

void Protocol::connected() {
    std::cout << "Login successful" << std::endl;

}

void Protocol::error(std::string errormsg) {
//to-do
}

bool Protocol::reciept(const std::string &id) {
    StompFrame *frame = Database::getInstance()->getReciept(id);
    bool logout = false;
    if (frame->getCommand() == SUBSCRIBE)
        std::cout << "Joind club " << frame->getHeaders()["destination"] << std::endl;
    else if (frame->getCommand() == UNSUBSCIRBE)

        std::cout << "Exited club " << frame->getHeaders()["destination"] << std::endl;
    else if (frame->getCommand() == DISCONNECT) {
        logout=true;
    }
    frame = nullptr;
    Database::getInstance()->removeReciept(id);
    return logout;
}

void Protocol::message(StompFrame frame) {
    std::vector<std::string> words = split_string_to_words_vector(frame.getBody());
    if ((words[0] == Database::getInstance()->getName())|(words.size()==1)) {
        std::cout << frame.getHeaders().find("destination")->second << ":" << frame.getBody() << std::endl;
    } else if (words[1] == "has") {
        std::string book;
        if(words[2]=="added") {
            book = bookFromVector(words, 5, words.size());
        } else {
            book = bookFromVector(words, 2, words.size());
        }
         if (Database::getInstance()->wantedToBorrow(book)) {
            borrow(frame.getBody(), frame.getHeaders()["destination"]);
        }
        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
    } else if (words[1] == "wish") {
        std::string book=bookFromVector(words,4,words.size());
        contains(frame.getHeaders()["destination"], book);
        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
    } else if ((words[0] == "Taking") & (words[words.size()-1] == Database::getInstance()->getName())) {
        std::string book=bookFromVector(words,1,words.size()-2);
        lend(frame.getHeaders()["destination"], book);
        std::cout << frame.getBody() << std::endl;
    } else if ((words[0] == "Returning") & (words[words.size()-1] == Database::getInstance()->getName())) {
        std::string book=bookFromVector(words,1,words.size()-2);
        getBack(frame.getHeaders()["destination"], book);
    } else if (words[1] == "status") {
        status(frame.getHeaders()["destination"]);
        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
    } else {
        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
    }

}

void Protocol::borrow(std::string msg, const std::string genre) {
    std::vector<std::string> words = split_string_to_words_vector(msg);
    Database::getInstance()->addBorrowedBook(genre, words[2], words[0]);
    StompFrame frame = StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination", genre);
    frame.setBody("Taking " + words[2] + " from " + words[0]);
    handler.sendFrameAscii(frame.toString(), '\0');
}

void Protocol::lend(std::string genre, std::string book) {
    Database::getInstance()->lendBook(genre, book);
}

void Protocol::status(std::string genre) {
    std::list<std::string> books = Database::getInstance()->getBooksByGenre(genre);
    StompFrame frame = StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination", genre);
    std::string status = Database::getInstance()->getName() + ":";
    for (auto book:books) {
        status += book + ",";
    }
    status.resize(status.size() - 1);
    frame.setBody(status);
    handler.sendFrameAscii(frame.toString(), '\0');
}

void Protocol::getBack(std::string genre, std::string book) {
    Database::getInstance()->addBook(genre, book);
}

void Protocol::contains(std::string genre, std::string book) {
    if (Database::getInstance()->contains(genre, book)) {
        StompFrame frame = StompFrame();
        frame.setCommand(SEND);
        frame.addHeader("destination", genre);
        frame.setBody(Database::getInstance()->getName() + " has " + book);
        handler.sendFrameAscii(frame.toString(), '\0');
    }
}


std::string Protocol::bookFromVector(std::vector<std::string> words, int start, int end) {
    std::string book;
    for(int i=start;i<end;i++)
        book+=words[i]+" ";
    book=book.substr(0,book.size()-1);
    return book;
}

