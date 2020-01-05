package bgu.spl.net.srv;

import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

public class User {
    public final String userName;
    public final String password;
    private int connectionId;
    private ConcurrentHashMap<Integer, String> subId_Topic_Map;
    private boolean loggedin;


    public User(String userName, String password, int connection_ID) {
        this.connectionId = connection_ID;
        this.userName = userName;
        this.password = password;
        subId_Topic_Map = new ConcurrentHashMap<>();
        loggedin = false;

    }

    public String getPassword() {
        return password;
    }


    public int getConnectionId() {
        return connectionId;
    }

    public void setConnectionId(int connectionId) {
        this.connectionId = connectionId;
    }

    public boolean isLoggedin() {
        return loggedin;
    }

    public void Login() {
        this.loggedin = true;
    }

    public void Addsubscrbtion(int subId, String topic) {
        subId_Topic_Map.putIfAbsent(subId, topic);
    }

    public void RemoveSubscribtion(int subId) {
        subId_Topic_Map.remove(subId);
    }

    public void Disconnect() {
        subId_Topic_Map.clear();
        loggedin = false;
    }
}
