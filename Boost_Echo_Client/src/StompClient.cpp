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
        input = "";
        std::getline(std::cin, input);

        if (input.find("login") != std::string::npos) {
            std::pair<std::string, short> handlerdata = InputProcessor::get_hostnip(input);
            handler = new ConnectionHandler(handlerdata.first, handlerdata.second);
            if (handler->connect()) {
                break;
            }
        }
    }
    std::string msg;
    msg = processor.process(input);
    handler->sendFrameAscii(msg, '\0');
    ServerTask task(*handler);
    std::thread t1(task);
    while (1) {
        input = "";
        std::getline(std::cin, input);
        std::string output = processor.process(input);
        handler->sendFrameAscii(output,'\0');
        if (output.find("DISCONNECT") != std::string::npos) {
            break;
        }

    }
    t1.join();
    delete Database::getInstance();
    delete handler;

    return 0;
}


