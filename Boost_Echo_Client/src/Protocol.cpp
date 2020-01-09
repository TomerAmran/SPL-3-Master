//
// Created by yuval on 08/01/2020.
//

#include "Protocol.h"

Protocol::Protocol(Database &inventory, ConnectionHandler &handler) : inventory(inventory), handler(handler),
                                                                      username(""),{}

void Protocol::processKeybord(std::string input) {


}

void Protocol::processServer(std::string msg) {

}

std::vector<std::string> Protocol::split_string_to_words_vector(std::string string) {
     std::istringstream iss(string);
    std::vector<std::string> words(std::istream_iterator<std::string>{iss},
                                   std::istream_iterator<std::string>());
    return words;
}

