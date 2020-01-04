package bgu.spl.net.srv;

import java.io.IOException;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

public class ConnectionsImpl<T> implements Connections<T> {

    private ConcurrentHashMap<Integer ,ConnectionHandler<T>> user_Map;
    private ConcurrentHashMap<String, ConcurrentLinkedQueue<Integer>> genere_Subscribtion_Map;
    public ConnectionsImpl(ConcurrentHashMap<Integer ,ConnectionHandler<T>> user_Map,ConcurrentHashMap<String, ConcurrentLinkedQueue<Integer>> genere_Subscribtion_Map)
    {
        this.user_Map=user_Map;
        this.genere_Subscribtion_Map=genere_Subscribtion_Map;
    }

    @Override
    public boolean send(int connectionId, T msg) {
        ConnectionHandler<T> handler=user_Map.get(connectionId);
        if (handler!=null) {
            handler.send(msg);
            return true;
        }
        return false;
    }

    @Override
    public void send(String channel, T msg) {
        ConcurrentLinkedQueue<Integer> queue=genere_Subscribtion_Map.get(channel);
        if(queue!=null)
        {
            for( Integer i:queue)
                send(i,msg);
        }
    }

    @Override
    public void disconnect(int connectionId) {
     for(String gener:genere_Subscribtion_Map.keySet())
            {
                genere_Subscribtion_Map.get(gener).remove(connectionId);
            }
        ConnectionHandler<T> toClose= user_Map.remove(connectionId);
        try {
            toClose.close();
        } catch (IOException ignore) {

        }


    }
}
