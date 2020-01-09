//
// Created by yuval on 09/01/2020.
//

#include "ServerTask.h"

ServerTask::ServerTask(ConnectionHandler &handler):handler(handler),protocol(Protocol(handler)) {
}

void ServerTask::run() {
    std::string msg;
    handler.getFrameAscii(msg,'\n');
    do
    {
        msg="";
        handler.getFrameAscii(msg,'\n');
    }while(!protocol.processServer(msg));
       handler.close();
}
