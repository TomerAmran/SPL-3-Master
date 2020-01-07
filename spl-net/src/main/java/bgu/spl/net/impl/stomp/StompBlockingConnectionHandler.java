package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.ConnectionHandler;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.net.Socket;

public class StompBlockingConnectionHandler  implements Runnable, ConnectionHandler<String> {
    private final StompMessagingProtocol protocol;
    private final MessageEncoderDecoder<String> encdec;
    private final Socket sock;
    private BufferedInputStream in;
    private BufferedOutputStream out;
    private volatile boolean connected = true;
    public StompBlockingConnectionHandler( Socket sock,MessageEncoderDecoder<String> encdec, StompMessagingProtocol protocol ) {
        this.protocol = protocol;
        this.encdec = encdec;
        this.sock = sock;
    }
    @Override
    public void run() {
        try(Socket sock =this.sock) {
            int read;
            in = new BufferedInputStream(sock.getInputStream());
            while (!protocol.shouldTerminate() && connected && (read = in.read()) >= 0) {
                String nextMessage = encdec.decodeNextByte((byte) read);
                if(nextMessage != null)
                    protocol.process(nextMessage);
            }
        }
        catch (IOException ex){ex.printStackTrace();}
    }
    @Override
    public void close() throws IOException {
        connected = false;
        sock.close();
    }
    public void send(String msg){
        try {
            out = new BufferedOutputStream(sock.getOutputStream());
            out.write(encdec.encode(msg));
            out.flush();
        }
        catch (IOException ex) {ex.printStackTrace();}

    }
}
