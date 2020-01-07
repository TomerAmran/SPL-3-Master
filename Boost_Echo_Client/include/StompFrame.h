//
// Created by yuval on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_STOMPFRAME_H
#define BOOST_ECHO_CLIENT_STOMPFRAME_H


#include <unordered_map>
#include <map>

enum Command{
    MESSAGE, RECEIPT, CONNECTED, SEND, SUBSCRIBE, CONNECT
};

class StompFrame {
public:
    StompFrame();
    void parse(std::string msg);
    std::string toString();
    void setCommand(Command command);
    void setBody(std::string body);
    void addHeader(std::string name,std::string value);
    std::map<std::string ,std::string >getHeaders();
    Command getCommand();
    std::string getBody();

private:
    Command command;
    std::map<std::string,std::string> headers;
    std::string body;
    std::map<std::string,Command> string_Enum_Convertor;
};

#endif //BOOST_ECHO_CLIENT_STOMPFRAME_H
