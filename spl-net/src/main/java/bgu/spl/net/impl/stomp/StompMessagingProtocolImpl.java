package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.DataBase;

import java.util.HashMap;

public class StompMessagingProtocolImpl implements StompMessagingProtocol {
    //fields
    private int connectionId;
    private Connections<String> connections;
    private DataBase database;
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
    public String process(String message){
        StompFrame frame = StompFrame.parse(message);
        switch (frame.getCommand()){
            case CONNECT:
                CONNECT_received(frame.getHeaders(), frame.getBody());
                break;
//            case CONNECTED:
//                CONNECTED_received(frame.getHeaders(), frame.getBody());
//                break;
//            case MESSAGE:
//                MESSAGE_received(frame.getHeaders(), frame.getBody());
//                break;
//            case RECEIPT:
//                RECEIPT_received(frame.getHeaders(), frame.getBody());
//                break;
//            case ERROR:
//                ERROR_received(frame.getHeaders(), frame.getBody());
//                break;
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
        return null;
    }
    private void CONNECT_received(HashMap<String,String> headers, String body){
        //deal with accept-version?
        //deal with host?
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
//    private void CONNECTED_received(HashMap<String,String> headers, String body){}
//    private void MESSAGE_received(HashMap<String,String> headers, String body){}
//    private void RECEIPT_received(HashMap<String,String> headers, String body){}
//    private void ERROR_received(HashMap<String,String> headers, String body){}
    private void SEND_received(HashMap<String,String> headers, String body){
        StompFrame message = new StompFrame();
        message.setCommand("MESSAGE");
        message.addHeader("destination",headers.get("destination"));
        message.addHeader("Message-id","1");
        message.setBody(body);
    }
    private void SUBSCRIBE_received(HashMap<String,String> headers, String body)
    {
        if((headers.get("receipt"))!=null) {
            StompFrame frame = new StompFrame();
            frame.setCommand("Recipt");
            frame
        }
        database.Subscribe(headers.get("destination"),headers.get("id"),connectionId);
    }
    private void UNSUBSCRIBE_received(HashMap<String,String> headers, String body)
    {
        if()
        StompFrame frame = new StompFrame();
        frame.setCommand("Recipt");
        database.Subscribe(headers.get("destination"),headers.get("id"),connectionId);
        //add subscription to connections

    }
    private void DISCONNECT_received(HashMap<String,String> headers, String body){}
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
        return true;
    }
}
