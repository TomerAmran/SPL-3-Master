package bgu.spl.net.srv;

import java.util.concurrent.ConcurrentHashMap;

public class DataBase {

    private ConcurrentHashMap<String,User> name_User_Map;
    private ConcurrentHashMap<String, ConcurrentHashMap<User,Integer>> topic_Subscribtion_Map;
    private ConcurrentHashMap<Integer,User> connectionId_User_Map;
    private  static DataBase instance=new DataBase();

    private DataBase()
    {
        topic_Subscribtion_Map =new ConcurrentHashMap<>();
        name_User_Map=new ConcurrentHashMap<>();
        connectionId_User_Map=new ConcurrentHashMap<>();
    }

    public static DataBase getInstance()
    {
        return instance;
    }
    public void AddUser(int connectionId,String username, String password)
    {
        User newUser=new User(username,password,connectionId);
        name_User_Map.put(username,newUser);
        newUser.Login();
    }
    public boolean DoesUserExists(String username)
    {
        if(name_User_Map.get(username)!=null)
            return true;
        return false;
    }
    public boolean IsPasswordCorrect(String username,String password)
    {
        return name_User_Map.get(username).password.equals(password);
    }
    public boolean IsLoggedIn(String username)
    {
        return name_User_Map.get(username).isLoggedin();
    }
    public void Login(String username)
    {
        name_User_Map.get(username).Login();
    }
    public void Subscribe(String topic, int subId,int connectionId)
    {
        topic_Subscribtion_Map.putIfAbsent(topic,new ConcurrentHashMap<>());
        topic_Subscribtion_Map.get(topic).putIfAbsent(connectionId_User_Map.get(connectionId),subId);
        connectionId_User_Map.get(connectionId).Addsubscrbtion(subId,topic);
    }
    public void Unsubscribe (String topic, int subId,int connectionId)
    {
        if( topic_Subscribtion_Map.get(topic)!=null) {
            topic_Subscribtion_Map.get(topic).remove(connectionId_User_Map.get(connectionId));
            connectionId_User_Map.get(connectionId).RemoveSubscribtion(subId);
        }
    }
    public void Disconnect(int connectionId)
    {
        User toDisconnect=connectionId_User_Map.get(connectionId);
        toDisconnect.Disconnect();
    }
    public int GetUserSubId(String topic,String username)
    {
        return topic_Subscribtion_Map.get(topic).get(username);
    }

}
