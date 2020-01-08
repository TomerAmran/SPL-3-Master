//
// Created by yuval on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_PROTOCOL_H
#define BOOST_ECHO_CLIENT_PROTOCOL_H

#include <Database.h>
#include <ConnectionHandler.h>

class Protocol {
public:
    Protocol(Database& inventory, ConnectionHandler& handler);
    void processKeybord(std::string input);
    void processServer(std::string msg);
private:
    Database& inventory;
    ConnectionHandler& handler;
    std::string username;
    std::vector<std::string> split_string_to_words_vector(std::string string);


};

#endif //BOOST_ECHO_CLIENT_PROTOCOL_H
