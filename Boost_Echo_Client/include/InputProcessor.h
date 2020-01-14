//
// Created by yuval on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_INPUTPROCESSOR_H
#define BOOST_ECHO_CLIENT_INPUTPROCESSOR_H

#include <vector>
#include <string>
class InputProcessor {
public:
    InputProcessor();
    std::string process(std::string input);
    static std::vector<std::string> split_string_to_words_vector(std::string string);
    static std::pair<std::string,short> get_hostnip(std::string);
private:
    int receipt_counter;
    int subId_counter;
    std::string login(std::vector<std::string>& words);
    std::string subscribe(std::vector<std::string>& words);
    std::string unsubscribe(std::vector<std::string>& words);
    std::string addBook(std::vector<std::string>& words);
    std::string borrow(std::vector<std::string>& words);
    std::string returnBook(std::vector<std::string>& words);
    std::string status(std::vector<std::string>& words);
    std::string logout(std::vector<std::string>& words);
    void logoutUnsubscribe();
    std::string bookFromVector(std::vector<std::string> words,int start,int end);



};

#endif //BOOST_ECHO_CLIENT_INPUTPROCESSOR_H
