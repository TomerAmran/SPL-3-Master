//
// Created by yuval on 08/01/2020.
//

#include <iterator>
#include <sstream>
#include <StompFrame.h>
#include <Database.h>
#include "InputProcessor.h"

InputProcessor::InputProcessor() : receipt_counter(1), subId_counter(1) {}

std::string InputProcessor::process(std::string input) {
    std::vector<std::string> words = split_string_to_words_vector(input);
    std::string output;
    if (words[0] == "login") {
        output = login(words);
    } else if (words[0] == "join") {
        output = subscribe(words);
    } else if (words[0] == "add") {
        output = addBook(words);
    } else if (words[0] == "borrow") {
        output = borrow(words);
    } else if (words[0] == "return") {
        output = returnBook(words);
    } else if (words[0] == "status") {
        output = status(words);
    } else if (words[0] == "exit") {
        output = unsubscribe(words);
    } else if (words[0] == "logout") {
        output = logout(words);
    }
    return output;
}

std::string InputProcessor::login(std::vector<std::string> &words) {
    StompFrame frame = StompFrame();
    frame.setCommand(CONNECT);
    frame.addHeader("accept-version", "1.2");
    frame.addHeader("host", "stomp.cs.bgu.ac.il");
    frame.addHeader("login", words[2]);
    frame.addHeader("passcode", words[3]);
    Database::getInstance()->setName(words[2]);
    return frame.toString();
}

std::string InputProcessor::subscribe(std::vector<std::string> &words) {
    StompFrame *frame = new StompFrame();
    frame->setCommand(SUBSCRIBE);
    frame->addHeader("destination", words[1]);
    frame->addHeader("id", std::to_string(subId_counter));
    frame->addHeader("receipt", std::to_string(receipt_counter));
    Database::getInstance()->addGenre(words[1], std::to_string(subId_counter));
    Database::getInstance()->addReciept(std::to_string(receipt_counter), frame);
    subId_counter++;
    receipt_counter++;
    return frame->toString();

}

std::string InputProcessor::unsubscribe(std::vector<std::string> &words) {
    StompFrame *frame = new StompFrame();
    frame->setCommand(UNSUBSCIRBE);
    frame->addHeader("id", Database::getInstance()->getSubid(words[1]));
    frame->addHeader("receipt", std::to_string(receipt_counter));
    Database::getInstance()->addReciept(std::to_string(receipt_counter), frame);
    return frame->toString();
}

std::string InputProcessor::addBook(std::vector<std::string> &words) {
    StompFrame frame = StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination", words[1]);
    std::string book = bookFromVector(words, 2, words.size());
    frame.setBody(Database::getInstance()->getName() + " has added the book " + book);
    Database::getInstance()->addBook(words[1], book);
    return frame.toString();

}

std::string InputProcessor::borrow(std::vector<std::string> &words) {
    StompFrame frame = StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination", words[1]);
    std::string book = bookFromVector(words, 2, words.size());
    frame.setBody(Database::getInstance()->getName() + " wish to borrow " + book);
    Database::getInstance()->addToBorrowList(book);
    return frame.toString();
}

std::string InputProcessor::returnBook(std::vector<std::string> &words) {
    StompFrame frame = StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination", words[1]);
    std::string book = bookFromVector(words, 2, words.size());
    frame.setBody(+"Returning  " + book + " to " + Database::getInstance()->getLoanerName(book));
    Database::getInstance()->deleteBook(words[1], words[2]);
    return frame.toString();
}

std::string InputProcessor::status(std::vector<std::string> &words) {
    StompFrame frame = StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination", words[1]);
    frame.setBody("book status");
    return frame.toString();

}

std::string InputProcessor::logout(std::vector<std::string> &words) {
    StompFrame *frame = new StompFrame();
    frame->setCommand(DISCONNECT);
    frame->addHeader("receipt", std::to_string(receipt_counter));
    Database::getInstance()->addReciept(std::to_string(receipt_counter), frame);
    return frame->toString();

};

std::vector<std::string> InputProcessor::split_string_to_words_vector(std::string string) {
    std::istringstream iss(string);
    std::vector<std::string> words(std::istream_iterator<std::string>{iss},
                                   std::istream_iterator<std::string>());
    return words;
}

std::pair<std::string, short> InputProcessor::get_hostnip(std::string input) {
    int split = input.find(':');
    std::string host = input.substr(6, split - 6);
    short port = std::stoi(input.substr(split + 1, 4));
    return std::make_pair(host, port);
}

std::string InputProcessor::bookFromVector(std::vector<std::string> words, int start, int end) {
    std::string book;
    for (int i = start; i < end; i++)
        book += words[i] + " ";
    book = book.substr(0, book.size() - 1);
    return book;
}




