package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.MessagingProtocol;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.BlockingConnectionHandler;
import bgu.spl.net.srv.Connections;

import java.net.Socket;

public class StompBlockingConnectionHandler extends BlockingConnectionHandler<String> {
    StompBlockingConnectionHandler(Socket sock, MessageEncoderDecoder<String> reader, StompMessagingProtocol protocol, Connections<String> connections, int connectionId){
        super(sock, reader, protocol);
        protocol.start(connectionId,connections);
    }
}
