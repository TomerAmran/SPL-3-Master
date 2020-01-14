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
    ConnectionHandler *handler= nullptr;
    Protocol *protocol = nullptr;
    InputProcessor* processor = nullptr;
    while (1) {
        userInput = "";
        std::getline(std::cin, userInput);
        if (userInput.find("login") == std::string::npos) {
            std::cout << "Please enter 'login' command"<<std::endl;
        }
        else {
            std::pair<std::string, short> handlerdata = InputProcessor::get_hostnip(userInput);
            handler = new ConnectionHandler(handlerdata.first, handlerdata.second);
            protocol = new Protocol(*handler);
            if (handler->connect()) {
                //send login request
                processor = new InputProcessor(*handler);
                processor->processAndSend(userInput);
                //get server response about login request
                std::string serverResponse= "";
                handler -> getFrameAscii(serverResponse, '\0');
                protocol -> processServer(serverResponse);
                if(protocol->isLoggedIn()) {
                    //Login Succesful!!!
                    break;
                }
            } else
            {
                delete handler;
                delete protocol;
            }

        }

    }

    ServerTask task(*handler, *protocol);
    std::thread MsgReceiverThread(task);

    //main loop
    while (1) {
        userInput = "";
        std::getline(std::cin, userInput);
        processor -> processAndSend(userInput);
        if (userInput.find("logout") != std::string::npos)
                break;
    }
    MsgReceiverThread.join();
    delete Database::getInstance();
    delete handler;
    delete protocol;
    delete processor;
    return 0;
}


