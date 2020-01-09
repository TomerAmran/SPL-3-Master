package bgu.spl.net.impl.stomp;

import bgu.spl.net.impl.rci.ObjectEncoderDecoder;
import bgu.spl.net.impl.rci.RemoteCommandInvocationProtocol;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.srv.Server;

public class StompServer {

    public static void main(String[] args) throws Exception {
        if (args.length < 2)
            throw new Exception("args should be:<port> <server-type>");
        int port = Integer.parseInt(args[0]);
        String serverType = args[1];

        if (serverType.equals("tpc")){
            Server.threadPerClient(
                    port,
                    StompMessagingProtocolImpl::new, //protocol factory
                    StompEncoderDecoder::new //message encoder decoder factory
            ).serve();
        }

        if (serverType.equals("reactor")){
            Server.reactor(
                    10,
                    port,
                    StompMessagingProtocolImpl::new, //protocol factory
                    StompEncoderDecoder::new
            ).serve(); //message encoder decoder factory)
        }



    }


}
