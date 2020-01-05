package bgu.spl.net.srv;

import java.util.concurrent.ConcurrentHashMap;

public class DataBase {

    private ConcurrentHashMap<User ,ConnectionHandler > user_Handler_Map;
    private ConcurrentHashMap<String, ConcurrentHashMap<User,Integer>> genere_Subscribtion_Map;
    private ConcurrentHashMap<Integer,User> connectionId_User_Map;
    private  static DataBase instance=new DataBase();

    private DataBase()
    {
        user_Handler_Map =new ConcurrentHashMap<>();
        genere_Subscribtion_Map=new ConcurrentHashMap<>();
        connectionId_User_Map=new ConcurrentHashMap<>();
    }

    public static DataBase getInstance()
    {
        return instance;
    }
    public void addUser(User newuser,ConnectionHandler handler)
    {
        user_Handler_Map.putIfAbsent(newuser,handler);

    }

    public void Subscribe(String topic, int subId,int connectionId)
    {
        genere_Subscribtion_Map.get(topic).putIfAbsent(connectionId_User_Map.get(connectionId),subId);
        connectionId_User_Map.get(connectionId).Addsubscrbtion(subId,topic);
    }
    public void Unsubscribe (String topic, int subId,int connectionId)
    {
            genere_Subscribtion_Map.get(topic).remove(connectionId_User_Map.get(connectionId));
            connectionId_User_Map.get(connectionId).RemoveSubscribtion(subId);
    }

    public ConnectionHandler getHandler(int connectionId)
    {
        return user_Handler_Map.get(connectionId_User_Map.get(connectionId));
    }
    public void Disconnect(int connectionId)
    {
        User todisconnect=connectionId_User_Map.get(connectionId);
        for(String gener:genere_Subscribtion_Map.keySet())
        {
            genere_Subscribtion_Map.get(gener).remove(todisconnect);
        }
        todisconnect.Disconnect();
           }

}
