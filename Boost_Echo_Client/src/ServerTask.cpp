//
// Created by yuval on 09/01/2020.
//

#include "ServerTask.h"

ServerTask::ServerTask(ConnectionHandler &handler):handler(handler),protocol(Protocol(handler)) {
}

void ServerTask::operator()() {
    std::string msg;
    do
    {
        msg="";
        handler.getFrameAscii(msg,'\0');
        bool logout=protocol.processServer(msg);
        if(logout) {
            break;
        }
    }while(1);

}
