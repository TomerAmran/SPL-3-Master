package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.StompMessagingProtocol;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.function.Supplier;

public class StompTPC {
    private final int port;
    private final Supplier<StompMessagingProtocol> protocolFactory;
    private final Supplier<MessageEncoderDecoder<String>> encdecFactory;
    private ServerSocket sock;

    public StompTPC(int port, Supplier<StompMessagingProtocol> protocolFactory, Supplier<MessageEncoderDecoder<String>> encdecFactory, ServerSocket sock) {
        this.port = port;
        this.protocolFactory = protocolFactory;
        this.encdecFactory = encdecFactory;
    }
    public void serve() {
        try (ServerSocket serverSock = new ServerSocket(port)) {
            System.out.println("Server started");
            this.sock = serverSock; //just to be able to close
            while (!Thread.currentThread().isInterrupted()) {
                Socket clientSock = serverSock.accept();
                StompBlockingConnectionHandler handler = new StompBlockingConnectionHandler(
                        clientSock,
                        encdecFactory.get(),
                        protocolFactory.get());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
