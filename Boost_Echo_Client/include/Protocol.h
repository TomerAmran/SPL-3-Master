//
// Created by yuval on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_PROTOCOL_H
#define BOOST_ECHO_CLIENT_PROTOCOL_H

#include <Database.h>
#include <ConnectionHandler.h>

class Protocol {
public:
    Protocol(ConnectionHandler& handler);
    //processing the recived input from the server
    void processServer(std::string msg);
    bool isLoggedOut();
    bool isLoggedIn();
private:
    ConnectionHandler& handler;
    //splits the input to vector of words
    std::vector<std::string> split_string_to_words_vector(const std::string& string);
    bool loggedOut;
    bool loggedIn;
    //reacting to connected frame
    void connected();
    //reacting to error frame
    void error(std::string errMsg);
    //reacting to reciept frame
    void reciept(const std::string& id);
    //reacting to message frame
    void message(StompFrame frame);
    //reacting to message frame that some one had a book that i wanted to borrow
    void borrow(std::vector<std::string> &words, const std::string genre, std::string book);
    //reacting to message frame containing: taking and from "username"
    void lend(std::string genre,std::string book);
    //reacting to message frame containing book status
    void status(std::string genre);
    //reacting to message frame containing returning and from username
    void getBack(std::string genre, std::string book);
    //reacting to want to borrow frame of other users
    void contains(std::string genre, std::string book);
    //retriving book name from vector of words
    std::string bookFromVector(std::vector<std::string>& words,int start,int end);
    //chosing the correct domain for retriving book name in an has..."bookname" message

};

#endif //BOOST_ECHO_CLIENT_PROTOCOL_H
