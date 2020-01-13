//
// Created by yuval on 09/01/2020.
//

#include "ServerTask.h"

ServerTask::ServerTask(ConnectionHandler &handler, Protocol& protocol):handler(handler),protocol(protocol) {
}

void ServerTask::operator()() {
    std::string msg;
    do
    {
        msg="";
        handler.getFrameAscii(msg,'\0');
        protocol.processServer(msg);
        if(!protocol.isLoggedIn()) {
            break;
        }
    }while(1);

}
