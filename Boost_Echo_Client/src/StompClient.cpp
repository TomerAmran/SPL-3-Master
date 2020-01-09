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

int main(int argc, char *argv[]) {
    std::string input;
    ConnectionHandler *handler = nullptr;
    InputProcessor processor = InputProcessor();
    while (1) {
        std::cout << "you are not connected" << std::endl;
        input = "";
        std::getline(std::cin, input);

         if (input.find("login") != std::string::npos) {
             std::pair<std::string, short> handlerdata = InputProcessor::get_hostnip(input);
             handler=new ConnectionHandler(handlerdata.first, handlerdata.second);
             if (handler->connect()) {
                 break;
             }
         }
     }
        std::string msg;
        msg = processor.process(input);
        handler->sendFrameAscii(msg,'\0');
    std::string answer;
    // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
    // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
    if (!handler->getFrameAscii(answer,'\0')) {
        std::cout << "Disconnected. Exiting...\n" << std::endl;
    }
        Protocol p=Protocol(*handler);

       /*  ServerTask task(*handler);
         std::thread t1(&ServerTask::run, &task);
         while (1) {
             input = "";
             std::getline(std::cin, input);
             std::string output = processor.process(input);
             if (output.find("Disconnect") != std::string::npos) {
                 break;
             }
             std::string input;
             ConnectionHandler *handler = nullptr;
             InputProcessor processor;
             std::getline(std::cin, input);
         }
         t1.join();
         delete Database::getInstance();
         delete handler;*/
        return 0;
    }


