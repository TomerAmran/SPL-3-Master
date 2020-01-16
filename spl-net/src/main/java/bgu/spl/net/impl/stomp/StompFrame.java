package bgu.spl.net.impl.stomp;


import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;

public class StompFrame {
    //fields
    public static enum Command {CONNECT, CONNECTED, MESSAGE, RECEIPT, ERROR, SEND, SUBSCRIBE, UNSUBSCRIBE, DISCONNECT,STOMP}
    private Command command;
    private LinkedHashMap<String,String> headers;
    private String body;

    public StompFrame(){
        headers = new LinkedHashMap<>();
        body = "";
    }

    public static StompFrame parse(String message){
        StompFrame f = new StompFrame();
        String[] mArr = message.split("\n");
        //set command
        f.command = Command.valueOf(mArr[0]);
        //set headers & body
        for (int i=1; i<mArr.length ; i++){
            if (mArr[i].length() == 0) {
                // "" signs end of headers
                if(mArr.length > i+1)
                    //there is another line which contains the StompBody
                    f.body = mArr[i+1];
                break;//there is nothing after body
            }
            else{
                //put header in headers map
                String[] header  = mArr[i].split(":");
                f.headers.put(header[0],header[1]);
            }
        }



        return f;
    }

    public String toString(){
        //Command
        String output = command.toString()+"\n";
        //Headers
        for (Map.Entry<String,String> entry : headers.entrySet()){
            String headerName = entry.getKey();
            String headerValue = entry.getValue();
            output = output + headerName+":"+headerValue+"\n";
        }
        //Body & endOfMesseage charcter
        output = output + "\n" + body;
        return output;
        }

    public void setCommand(String command) {
        this.command = Command.valueOf(command);
    }

    public void addHeader(String headerName, String headerValue) {
        headers.put(headerName,headerValue);
    }

    public void setBody(String body) {
        this.body = body;
    }

    public Command getCommand() {
        return command;
    }

    public HashMap<String, String> getHeaders() {
        return headers;
    }

    public String getBody() {
        return body;
    }
}
