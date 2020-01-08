//
// Created by yuval on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_INPUTPROCESSOR_H
#define BOOST_ECHO_CLIENT_INPUTPROCESSOR_H

#include <vector>
#include <string>
class InputProcessor {
    InputProcessor();
    std::string process(std::string input);
private:
    std::vector<std::string> split_string_to_words_vector(std::string string);
    std::string login(std::vector<std::string>& words);
    std::string subscribe(std::vector<std::string>& words);
    std::string unsubscribe(std::vector<std::string>& words);
    std::string addBook(std::vector<std::string>& words);
    std::string borrow(std::vector<std::string>& words);
    std::string returnBook(std::vector<std::string>& words);
    std::string status(std::vector<std::string>& words);
    std::string logout(std::vector<std::string>& words);
    int receipt_counter;
    int subId_counter;
    std::string username;

};

#endif //BOOST_ECHO_CLIENT_INPUTPROCESSOR_H
