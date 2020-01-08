//
// Created by yuval on 07/01/2020.
//

#include <vector>
#include <sstream>
#include "StompFrame.h"

StompFrame::StompFrame():headers(std::map<std::string,std::string>()) {
    string_Enum_Convertor.insert(std::make_pair("CONNECTED",CONNECTED));
    string_Enum_Convertor.insert(std::make_pair("RECEIPT",RECEIPT));
    string_Enum_Convertor.insert(std::make_pair("MESSAGE",MESSAGE));
    string_Enum_Convertor.insert(std::make_pair("ERROR",ERROR));
}

void StompFrame::parse(std::string msg) {
    std::vector<std::string> lines;
    std::istringstream stream(msg);
    std::string line;
    while(std::getline(stream, line)) {
        lines.push_back(line);
    }
    command=string_Enum_Convertor[lines[0]];
    int i=1;
    while(lines[i]!="")
    {
        int split=lines[i].find(':');
        headers.insert(std::make_pair(lines[i].substr(0,split),lines[i].substr(split+1,lines[i].size())));
        i++;
    }
    body=lines[i+1];
}

std::string StompFrame::toString() {

    std::string output;
    output=command+"\n";
    for(auto  p:headers)
    {
        output=output+p.first+p.second+"\n";

    }
    output=output+""+"\n";
    output=output+body+"\0";
    return output;

}

void StompFrame::setCommand(Command command) {
    this->command=command;
}

void StompFrame::setBody(std::string body) {
    this->body=body;
}

void StompFrame::addHeader(std::string name, std::string value) {
    headers.insert(std::make_pair(name,value));
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
