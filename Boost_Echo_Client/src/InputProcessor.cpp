//
// Created by yuval on 08/01/2020.
//class for processin the user input

#include <iterator>
#include <sstream>
#include <StompFrame.h>
#include <Database.h>
#include "InputProcessor.h"

InputProcessor::InputProcessor(ConnectionHandler& connectionHandler) : conHndlr(connectionHandler), receipt_counter(1), subId_counter(1) {}

//parsin the user input and reacting accordingly
void InputProcessor::processAndSend(std::string input) {
    std::vector<std::string> words = split_string_to_words_vector(input);
    std::string output;
    if (words[0] == "login") {
        login(words);
    } else if (words[0] == "join") {
        subscribe(words);
    } else if (words[0] == "add") {
        addBook(words);
    } else if (words[0] == "borrow") {
        borrow(words);
    } else if (words[0] == "return") {
        returnBook(words);
    } else if (words[0] == "status") {
        status(words);
    } else if (words[0] == "exit") {
        unsubscribe(words);
    } else if (words[0] == "logout") {
        logout(words);
    }

}
//creating the login frame be sent and setting the user name
void InputProcessor::login(std::vector<std::string> &words) {
    StompFrame frame = StompFrame();
    frame.setCommand(CONNECT);
    frame.addHeader("accept-version", "1.2");
    frame.addHeader("host", "stomp.cs.bgu.ac.il");
    frame.addHeader("login", words[2]);
    frame.addHeader("passcode", words[3]);
    Database::getInstance()->setName(words[2]);
    conHndlr.sendFrameAscii(frame.toString(),'\0');
}
//creating the subscribe frame to be sent, saving the recipt and subid
void InputProcessor::subscribe(std::vector<std::string> &words) {
    StompFrame *frame = new StompFrame();
    frame->setCommand(SUBSCRIBE);
    frame->addHeader("destination", words[1]);
    frame->addHeader("id", std::to_string(subId_counter));
    frame->addHeader("receipt", std::to_string(receipt_counter));
    Database::getInstance()->addReciept(std::to_string(receipt_counter), frame);
    subId_counter++;
    receipt_counter++;
    conHndlr.sendFrameAscii(frame->toString(),'\0');

}
//creating the unsubscribe frame to be sent and saving the reciept
void InputProcessor::unsubscribe(std::vector<std::string> &words) {
    StompFrame *frame = new StompFrame();
    frame->setCommand(UNSUBSCIRBE);
    frame->addHeader("id", Database::getInstance()->getSubid(words[1]));
    frame->addHeader("receipt", std::to_string(receipt_counter));
    Database::getInstance()->addReciept(std::to_string(receipt_counter), frame);
    receipt_counter++;
    conHndlr.sendFrameAscii(frame->toString(),'\0');
}
// creating the send frame to be sent and saving book
void InputProcessor::addBook(std::vector<std::string> &words) {
    StompFrame frame = StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination", words[1]);
    std::string book = bookFromVector(words, 2, words.size());
    frame.setBody(Database::getInstance()->getName() + " has added the book " + book);
    Database::getInstance()->addBook(words[1], book);
    conHndlr.sendFrameAscii(frame.toString(),'\0');

}
// creating the send frame to be sent and adding the book to the borrow list
void InputProcessor::borrow(std::vector<std::string> &words) {
    StompFrame frame = StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination", words[1]);
    std::string book = bookFromVector(words, 2, words.size());
    frame.setBody(Database::getInstance()->getName() + " wish to borrow " + book);
    Database::getInstance()->addToBorrowList(book);
    conHndlr.sendFrameAscii(frame.toString(),'\0');
}
// creating the send frame to be sent and removing the book from inventory
void InputProcessor::returnBook(std::vector<std::string> &words) {
    StompFrame frame = StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination", words[1]);
    std::string book = bookFromVector(words, 2, words.size());
    frame.setBody(+"Returning  " + book + " to " + Database::getInstance()->getLoanerName(book));
    Database::getInstance()->deleteBook(words[1], words[2]);
    conHndlr.sendFrameAscii(frame.toString(),'\0');
}
// creating the send frame to be sent
void InputProcessor::status(std::vector<std::string> &words) {
    StompFrame frame = StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination", words[1]);
    frame.setBody("book status");
    conHndlr.sendFrameAscii(frame.toString(),'\0');

}
//creating the disconnect frame to be sent, saving the recipt
void InputProcessor::logout(std::vector<std::string> &words) {
    logoutUnsubscribe();
  //  Database::getInstance()->canLogOut();//graceful shoutdown impl
    StompFrame *frame = new StompFrame();
    frame->setCommand(DISCONNECT);
    frame->addHeader("receipt", std::to_string(receipt_counter));
    Database::getInstance()->addReciept(std::to_string(receipt_counter), frame);
    conHndlr.sendFrameAscii(frame->toString(),'\0');

};
//spliting lines to vector of words
std::vector<std::string> InputProcessor::split_string_to_words_vector(std::string string) {
    std::istringstream iss(string);
    std::vector<std::string> words(std::istream_iterator<std::string>{iss},
                                   std::istream_iterator<std::string>());
    return words;
}
//parsing the host and port from input
std::pair<std::string, short> InputProcessor::get_hostnip(std::string input) {
    int split = input.find(':');
    std::string host = input.substr(6, split - 6);
    short port = std::stoi(input.substr(split + 1, 4));
    return std::make_pair(host, port);
}
// recovering book name from vector of words
std::string InputProcessor::bookFromVector(std::vector<std::string> words, int start, int end) {
    std::string book;
    for (int i = start; i < end; i++)
        book += words[i] + " ";
    book = book.substr(0, book.size() - 1);
    return book;
}

void InputProcessor::logoutUnsubscribe() {
        for(auto genre:Database::getInstance()->getGenreList())
        {
            std::vector<std::string> words=std::vector<std::string>();
           words.push_back("exit");
           words.push_back(genre);
           unsubscribe(words);

        }
}




