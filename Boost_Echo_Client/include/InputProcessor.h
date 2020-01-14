//
// Created by yuval on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_INPUTPROCESSOR_H
#define BOOST_ECHO_CLIENT_INPUTPROCESSOR_H

#include <vector>
#include <string>
#include "ConnectionHandler.h"

class InputProcessor {
public:
    InputProcessor(ConnectionHandler& connectionHandler);
    void processAndSend(std::string input);
    static std::vector<std::string> split_string_to_words_vector(std::string string);
    static std::pair<std::string,short> get_hostnip(std::string);
private:
    class ConnectionHandler& conHndlr;
    int receipt_counter;
    int subId_counter;
    void login(std::vector<std::string>& words);
    void subscribe(std::vector<std::string>& words);
    void unsubscribe(std::vector<std::string>& words);
    void addBook(std::vector<std::string>& words);
    void borrow(std::vector<std::string>& words);
    void returnBook(std::vector<std::string>& words);
    void status(std::vector<std::string>& words);
    void logout(std::vector<std::string>& words);
    void logoutUnsubscribe();
    std::string bookFromVector(std::vector<std::string> words,int start,int end);




};

#endif //BOOST_ECHO_CLIENT_INPUTPROCESSOR_H
