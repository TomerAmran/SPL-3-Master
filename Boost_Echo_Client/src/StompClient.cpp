//
// Created by yuval on 09/01/2020.
//

#include <string>
#include <iostream>
#include <vector>
#include <InputProcessor.h>
#include <ConnectionHandler.h>
#include <thread>
#include <ServerTask.h>
#include "Protocol.h"

int main(int argc, char *argv[]) {
    std::string userInput;
    ConnectionHandler *handler = nullptr;
    Protocol *protocol = nullptr;
    InputProcessor processor = InputProcessor();//why not in the heap?
    while (1) {
        userInput = "";
        std::getline(std::cin, userInput);
        if (userInput.find("login") != std::string::npos) {
            std::pair<std::string, short> handlerdata = InputProcessor::get_hostnip(userInput);
            handler = new ConnectionHandler(handlerdata.first, handlerdata.second);
            protocol = new Protocol(*handler);
            if (handler->connect()) {
                std::string serverResponse= "";
                handler -> getFrameAscii(serverResponse, '\0');
                protocol -> processServer(serverResponse);
                if(protocol->isLoggedIn()) {
                    //Login Succesful!!!
                    std::cout << "login succes";
                    break;
                }
            }
        }
        else{
            std::cout << "Please enter 'login' command";
        }
    }
    ServerTask task(*handler, *protocol);
    std::thread MsgReceiverThread(task);

    //main loop
    while (1) {
        userInput = "";
        std::getline(std::cin, userInput);
        std::string toSend = processor.process(userInput);
        handler->sendFrameAscii(toSend, '\0');
        if (userInput.find("logout") != std::string::npos)
                break;
    }
    MsgReceiverThread.join();
    delete Database::getInstance();
    delete handler;
    return 0;
}


