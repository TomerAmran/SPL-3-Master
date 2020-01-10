//
// Created by yuval on 09/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SERVERTASK_H
#define BOOST_ECHO_CLIENT_SERVERTASK_H

#include "ConnectionHandler.h"
#include "Protocol.h"

class ServerTask {
public:
    ServerTask(ConnectionHandler& handler);
    void operator()();
private:
    Protocol protocol;
    ConnectionHandler& handler;
};

#endif //BOOST_ECHO_CLIENT_SERVERTASK_H
