package bgu.spl.net.srv;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

public class ConnectionsImpl<T> implements Connections<T> {
    private ConcurrentHashMap<String, ConcurrentLinkedQueue<Integer>> topic_Subscribtion_Map;
    private ConcurrentHashMap<Integer ,ConnectionHandler<T>> connectionId_Handler_Map;

    public ConnectionsImpl()
    {
        topic_Subscribtion_Map =new ConcurrentHashMap<>();
        connectionId_Handler_Map=new ConcurrentHashMap<>();
    }
    @Override
    public boolean send(int connectionId, T msg) {
        ConnectionHandler<T> handler=connectionId_Handler_Map.get(connectionId);
        if (handler!=null) {
            handler.send(msg);
            return true;
        }
        return false;
    }

    @Override
    public void send(String channel, T msg) {
      //not going to be used cus personalization of the message should happen in the protocol
        ConcurrentLinkedQueue<Integer> queue = topic_Subscribtion_Map.get(channel);
        for(int connectionId : queue)
            send(connectionId,msg);


    }

    @Override
    public void disconnect(int connectionId) {
        for(String genre: topic_Subscribtion_Map.keySet())
        {
            topic_Subscribtion_Map.get(genre).remove(connectionId);
        }
        connectionId_Handler_Map.remove(connectionId);

    }
    public  void AddHandler(int connectionId,ConnectionHandler<T> handler)
    {
        connectionId_Handler_Map.put(connectionId,handler);
    }

    public void AddSubscription(String channel,int connectionId)
    {
        topic_Subscribtion_Map.putIfAbsent(channel,new ConcurrentLinkedQueue<>());
        topic_Subscribtion_Map.get(channel).add(connectionId);
    }
}
