package bgu.spl.net.srv;

import java.io.IOException;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

public class ConnectionsImpl<T> implements Connections<T> {



    @Override
    public boolean send(int connectionId, T msg) {
        ConnectionHandler<T> handler=DataBase.getInstance().getHandler(connectionId);
        if (handler!=null) {
            handler.send(msg);
            return true;
        }
        return false;
    }

    @Override
    public void send(String channel, T msg) {
      /*  ConcurrentLinkedQueue<Integer[]> queue=genere_Subscribtion_Map.get(channel);
        if(queue!=null)
        {
            for( Integer[] i:queue)
                send(i[1],msg);
        }*/
    }

    @Override
    public void disconnect(int connectionId) {


    }
}
