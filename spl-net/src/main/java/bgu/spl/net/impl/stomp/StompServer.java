package bgu.spl.net.impl.stomp;

import bgu.spl.net.impl.rci.ObjectEncoderDecoder;
import bgu.spl.net.impl.rci.RemoteCommandInvocationProtocol;
import bgu.spl.net.srv.Server;

public class StompServer {

    public static void main(String[] args) throws Exception {
        if (args.length < 2)
            throw new Exception("args should be: <port> <server type>");
        int port = Integer.getInteger(args[0]);
        String serverType = args[1];

        if (serverType.equals("tpc")){
            Server.threadPerClient(
                    port,
                    () -> new StompProtocol(), //protocol factory
                    ObjectEncoderDecoder::new //message encoder decoder factory
            ).serve();
        }
        if (serverType.equals("reactor")){}



    }


}
