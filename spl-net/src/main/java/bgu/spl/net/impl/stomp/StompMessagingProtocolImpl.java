package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.DataBase;

import java.util.HashMap;

public class StompMessagingProtocolImpl implements StompMessagingProtocol<String> {
    //fields
    private int connectionId;
    private Connections<String> connections;
    private DataBase database;
    private Boolean shouldTerminate =false;
    /**
     * Used to initiate the current client protocol with it's personal connection ID and the connections implementation
     **/
    @Override
    public void start(int connectionId, Connections<String> connections){
        this.connectionId = connectionId;
        this.connections = connections;
        database = DataBase.getInstance();
    }
    @Override
    public void process(String message){
        System.out.println("process called");
        StompFrame frame = StompFrame.parse(message);
        switch (frame.getCommand()){
            case CONNECT:
                CONNECT_received(frame.getHeaders());
                break;
            case SEND:
                SEND_received(frame.getHeaders(), frame.getBody());
                break;
            case SUBSCRIBE:
                SUBSCRIBE_received(frame.getHeaders(), frame.getBody());
                break;
            case UNSUBSCRIBE:
                UNSUBSCRIBE_received(frame.getHeaders(), frame.getBody());
                break;
            case DISCONNECT:
                DISCONNECT_received(frame.getHeaders(), frame.getBody());
                break;
        }

    }
    private void CONNECT_received(HashMap<String,String> headers){
        //deal with accept-version?
        //deal with host?
        System.out.println("conecet recived");
        String username = headers.get("login");
        String passcode = headers.get("passcode");
        //new user
        if(!database.DoesUserExists(username)) {
            database.AddUser(connectionId,username,passcode);
            sendCONNECTED(headers);
        }
        else{//user exist
            if(!database.IsPasswordCorrect(username,passcode))//wrong passcode
                sendWrongPasswordError();
            else
                if(!database.IsLoggedIn(username))
                    sendUserAlreadyLoggedInError();
                else {
                    database.Login(username);
                    sendCONNECTED(headers);
                }

        }

    }
    private void SEND_received(HashMap<String,String> headers, String body){
        StompFrame message = new StompFrame();
        for(int connectionId:database.GetUserSubIdsSubscribedToTopic(headers.get("destination")))
        {
            message.setCommand("MESSAGE");
            message.addHeader("subscription",database.GetUserSubId(headers.get("destination"),connectionId));
            message.addHeader("Message-id",(database.getAndIncreaseMessageCounter().toString()));
            message.addHeader("destination",headers.get("destination"));
            message.setBody(body);
            connections.send(connectionId,message.toString());

        }
    }
    private void SUBSCRIBE_received(HashMap<String,String> headers, String body) {
        database.Subscribe(headers.get("destination"), Integer.parseInt(headers.get("id")), connectionId);
        //subscribe in connections
        if ((headers.get("receipt")) != null) {
            StompFrame frame = new StompFrame();
            frame.setCommand("Recipt");
            frame.addHeader("receipt-id", headers.get("receipt"));
            connections.send(connectionId, frame.toString());
        }
    }
    private void UNSUBSCRIBE_received(HashMap<String,String> headers, String body) {
        database.Unsubscribe(Integer.parseInt(headers.get("id")),connectionId);
        //add subscription to connections
        StompFrame frame = new StompFrame();
        if((headers.get("receipt")) != null) {
            frame.setCommand("Recipt");
            frame.addHeader("receipt-id",headers.get("receipt"));
            connections.send(connectionId,frame.toString());
        }
    }
    private void DISCONNECT_received(HashMap<String,String> headers, String body){
        database.Disconnect(connectionId);
        if ((headers.get("receipt")) != null) {
            StompFrame frame = new StompFrame();
            frame.setCommand("Recipt");
            frame.addHeader("receipt-id", headers.get("receipt"));
            connections.send(connectionId, frame.toString());
        }
        shouldTerminate =true;

    }
    private void sendCONNECTED(HashMap<String,String> headers){
        StompFrame frame = new StompFrame();
        frame.setCommand("CONNECTED");
        frame.addHeader("version",headers.get("accept-version"));
        connections.send(connectionId, frame.toString());
    }
    private void sendWrongPasswordError(){
        StompFrame f = new StompFrame();
        f.setCommand("ERROR");
        f.addHeader("message","Wrong password");
        connections.send(connectionId,f.toString());
    }
    private void sendUserAlreadyLoggedInError(){
        StompFrame f = new StompFrame();
        f.setCommand("ERROR");
        f.addHeader("message","User already logged in");
        connections.send(connectionId,f.toString());
    }

    /**
     * @return true if the connection should be terminated
     */
    @Override
    public boolean shouldTerminate(){
        return shouldTerminate;
    }
}
