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
    bool processServer(std::string msg);
private:
    ConnectionHandler& handler;
    std::vector<std::string> split_string_to_words_vector(const std::string& string);
    void connected();
    void error(std::string errormsg);
    bool reciept(const std::string& id);
    void message(StompFrame frame);
    void borrow(std::string msg,const std::string genre);
    void lend(std::string genre,std::string book);
    void status(std::string genre);
    void getBack(std::string genre, std::string book);
    void contains(std::string genre, std::string book);
    std::string bookFromVector(std::vector<std::string> words,int start,int end);

};

#endif //BOOST_ECHO_CLIENT_PROTOCOL_H
