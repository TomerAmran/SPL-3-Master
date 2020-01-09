package bgu.spl.net.srv;

import java.io.IOException;

public interface Connections<T> {

    boolean send(int connectionId, T msg);

    void send(String channel, T msg);

    void disconnect(int connectionId);

    public  void AddHandler(int connectionId,ConnectionHandler<T> handler);

    public void AddSubscription(String channel,int connectionId);
}
