//
// Created by yuval on 08/01/2020.
//

#include "Protocol.h"

Protocol::Protocol(ConnectionHandler &handler) : handler(handler) {}

void Protocol::processServer(std::string msg) {
    StompFrame frame = StompFrame();
    frame.parse(msg);
    if (frame.getCommand() == CONNECTED) {
        connected();
    } else if (frame.getCommand() == ERROR) {
        error(frame.getBody());
    } else if (frame.getCommand() == RECEIPT) {
        reciept(frame.getHeaders()["receipt-id"]);
    } else if (frame.getCommand() == MESSAGE) {
        message(frame);
    }

}

std::vector<std::string> Protocol::split_string_to_words_vector(const std::string& string) {
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

void Protocol::reciept(const std::string& id) {
    StompFrame *frame = Database::getInstance()->getReciept(id);
    if (frame->getCommand() == SUBSCRIBE)
        std::cout << "Joind club " << frame->getHeaders()["destination"] << std::endl;
    else if (frame->getCommand() == UNSUBSCIRBE)
        std::cout << "Exited club " << frame->getHeaders()["destination"] << std::endl;
    else if (frame->getCommand() == DISCONNECT)
        handler.close();
    frame = nullptr;
    Database::getInstance()->removeReciept(id);
}

void Protocol::message(StompFrame &frame) {
    std::vector<std::string> words = split_string_to_words_vector(frame.getBody());
    if (words[0] == Database::getInstance()->getName()) {
        std::cout << frame.getHeaders().find("destination")->second << ":" << frame.getBody() << std::endl;
    } else if (words[2] == "has") {
        if (Database::getInstance()->wantedToBorrow(words[3])) {
            borrow(frame.getBody(), frame.getHeaders()["destination"]);
        }
        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
    } else if ((words[0] == "Taking") & (words[3] == Database::getInstance()->getName())) {
        lend(frame.getHeaders().find("destination")->second, words[1]);
        std::cout << frame.getBody() << std::endl;
    } else if ((words[0] == "Returning") & (words[3] == Database::getInstance()->getName())) {
        getBack(frame.getHeaders()["destination"], words[1]);
    } else if (words[1] == "status") {
        status(frame.getHeaders()["destination"]);
        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
    }

}

void Protocol::borrow(std::string msg, const std::string& genre) {
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
    for (const auto& book:books) {
        status += book + ",";
    }
    status.resize(status.size()-1);
    frame.setBody(status);
    handler.sendFrameAscii(frame.toString(), '\0');
}

void Protocol::getBack(std::string genre, std::string book) {
    Database::getInstance()->addBook(genre, book);
}

