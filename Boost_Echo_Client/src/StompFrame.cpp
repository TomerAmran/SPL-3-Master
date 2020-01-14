//
// Created by yuval on 07/01/2020.
//

#include <vector>
#include <sstream>
#include <iostream>
#include "StompFrame.h"

StompFrame::StompFrame() : command(NONE), headers(std::map<std::string, std::string>()),
                           body(""), string_Enum_Convertor(std::map<std::string, Command>()),
                           enum_string_convertor(std::map<Command, std::string>()) {
    string_Enum_Convertor.insert(std::make_pair("CONNECTED", CONNECTED));
    string_Enum_Convertor.insert(std::make_pair("RECEIPT", RECEIPT));
    string_Enum_Convertor.insert(std::make_pair("MESSAGE", MESSAGE));
    string_Enum_Convertor.insert(std::make_pair("ERROR", ERROR));
    enum_string_convertor.insert(std::make_pair(CONNECT, "CONNECT"));
    enum_string_convertor.insert(std::make_pair(SUBSCRIBE, "SUBSCRIBE"));
    enum_string_convertor.insert(std::make_pair(UNSUBSCIRBE, "UNSUBSCRIBE"));
    enum_string_convertor.insert(std::make_pair(SEND, "SEND"));
    enum_string_convertor.insert(std::make_pair(DISCONNECT, "DISCONNECT"));
}

void StompFrame::parse(const std::string msg) {
    if (msg == "") {
//        std::cout <<"EMPTY MSG";
        return;
    } else {
        std::vector<std::string> lines;
        std::istringstream stream(msg);
        std::string line;
        while (std::getline(stream, line)) {
            lines.push_back(line);
        }
        command = string_Enum_Convertor[lines[0]];
        int i = 1;
        while ((unsigned) i < lines.size() && lines[i] != "") {
            int split = lines[i].find(':');
            headers.insert(std::make_pair(lines[i].substr(0, split), lines[i].substr(split + 1, lines[i].size())));
            i++;
        }
        if ((unsigned) i < lines.size() - 1)
            body = lines[i + 1];
        else
            body = "";
    }
}

std::string StompFrame::toString() {
    std::string output;
    output = enum_string_convertor[command] + "\n";
    for (auto p:headers) {
        output = output + p.first + ":" + p.second + "\n";

    }
    output = output + "" + "\n";
    output = output + body;
    return output;

}

void StompFrame::setCommand(Command command) {
    this->command = command;
}

void StompFrame::setBody(std::string body) {
    this->body = body;
}

void StompFrame::addHeader(std::string name, std::string value) {
    headers.insert(std::make_pair(name, value));
}

std::map<std::string, std::string> StompFrame::getHeaders() {
    return headers;
}

Command StompFrame::getCommand() {
    return command;
}

std::string StompFrame::getBody() {
    return body;
}
