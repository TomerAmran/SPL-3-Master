//
// Created by yuval on 08/01/2020.
//

#include <iterator>
#include <sstream>
#include <StompFrame.h>
#include <Database.h>
#include "InputProcessor.h"
InputProcessor::InputProcessor():receipt_counter(1),subId_counter(1){}
std::string InputProcessor::process(std::string input) {
    std::vector<std::string> words = split_string_to_words_vector(input);
    std::string output;
    if (words[0] == "login") {
       output= login(words);
    } else if (words[0] == "join") {
        output= subscribe(words);
    } else if (words[0] == "add") {
        output=  addBook(words);
    } else if (words[0] == "borrow") {
        output= borrow(words);
    } else if (words[0] == "return") {
        output=    returnBook(words);
    } else if (words[0] == "status") {
        output=   status(words);
    } else if (words[0]=="exit"){
        output=unsubscribe(words);
    }else if (words[0] == "logout") {
        StompFrame* frame=new StompFrame();
        frame->setCommand(DISCONNECT);
        frame->addHeader("receipt",std::to_string(receipt_counter));
        output=frame->toString();
        Database::getInstance()->addReciept(std::to_string(receipt_counter),frame);
    }
    return output;
}

std::string InputProcessor::login(std::vector<std::string> &words) {
    StompFrame frame=StompFrame();
    frame.setCommand(CONNECT);
    frame.addHeader("accept-version","1.2");
    frame.addHeader("login",words[3]);
    frame.addHeader("passcode",words[4]);
    Database::getInstance()->setName(words[3]);
    return frame.toString();
}

std::string InputProcessor::subscribe(std::vector<std::string> &words) {
    StompFrame* frame= new StompFrame();
    frame->setCommand(SUBSCRIBE);
    frame->addHeader("destination",words[1]);
    frame->addHeader("id",std::to_string(subId_counter));
    frame->addHeader("receipt",std::to_string(receipt_counter));
    subId_counter++;
    receipt_counter++;
    Database::getInstance()->addGenre(words[1],std::to_string(subId_counter));
    Database::getInstance()->addReciept(std::to_string(receipt_counter),frame);
    return frame->toString();

}
std::string InputProcessor::unsubscribe(std::vector<std::string> &words) {
    StompFrame* frame= new StompFrame();
    frame->setCommand(UNSUBSCIRBE);
    frame->addHeader("receipt",std::to_string(receipt_counter));
    Database::getInstance()->addReciept(std::to_string(receipt_counter),frame);
    return frame->toString();
}
std::string InputProcessor::addBook(std::vector<std::string> &words) {
    StompFrame frame=StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination",words[1]);
    frame.setBody(Database::getInstance()->getName()+" has added the book "+words[2]);
    Database::getInstance()->addBook(words[1],words[2]);
    return  frame.toString();

}

std::string InputProcessor::borrow(std::vector<std::string> &words) {
    StompFrame frame=StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination",words[1]);
    frame.setBody(Database::getInstance()->getName()+" wish to borrow  "+words[2]);
    Database::getInstance()->addToBorrowList(words[2]);
    return frame.toString();
}

std::string InputProcessor::returnBook(std::vector<std::string> &words) {
    StompFrame frame=StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination",words[1]);
    frame.setBody(+"Returning  "+words[2]+" to "+Database::getInstance()->getLoanerName(words[2]));
    Database::getInstance()->addToBorrowList(words[2]);
    Database::getInstance()->deleteBook(words[1],words[2]);
    return frame.toString();
}

std::string InputProcessor::status(std::vector<std::string> &words) {
    StompFrame frame=StompFrame();
    frame.setCommand(SEND);
    frame.addHeader("destination",words[1]);
    frame.setBody("book status");
    return  frame.toString();

}

std::string InputProcessor::logout(std::vector<std::string> &words) {
    StompFrame* frame=new StompFrame();
    frame->setCommand(DISCONNECT);
    frame->addHeader("receipt",std::to_string(receipt_counter));
    Database::getInstance()->addReciept(std::to_string(receipt_counter),frame);
    return frame->toString();

};

std::vector<std::string> InputProcessor::split_string_to_words_vector(std::string string) {
    std::istringstream iss(string);
    std::vector<std::string> words(std::istream_iterator<std::string>{iss},
                                   std::istream_iterator<std::string>());
    return words;
}




