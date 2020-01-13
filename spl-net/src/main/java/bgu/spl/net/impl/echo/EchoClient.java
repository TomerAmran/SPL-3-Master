package bgu.spl.net.impl.echo;

import bgu.spl.net.impl.stomp.StompEncoderDecoder;

import java.io.*;
import java.net.Socket;

public class EchoClient {

    public static void main(String[] args) throws IOException {
        StompEncoderDecoder endc = new StompEncoderDecoder();
        if (args.length == 0) {
            args = new String[]{"localhost", "hello"};
        }

        if (args.length < 2) {
            System.out.println("you must supply two arguments: host, message");
            System.exit(1);
        }

        //BufferedReader and BufferedWriter automatically using UTF-8 encoding
        try (Socket sock = new Socket(args[0], 7777);
             BufferedInputStream in = new BufferedInputStream(sock.getInputStream());
             BufferedOutputStream out = new BufferedOutputStream(sock.getOutputStream());) {
            System.out.println("socketIsNull = " +(sock==null));
            System.out.println("sending message to server");

            out.write(endc.encode("CONNECT\n" +
                    "accept-version:1.2\n" +
                    "host:stomp.cs.bgu.ac.il\n" +
                    "login:bob\n" +
                    "passcode:alice\n" +
                    "\n"+
                    "^@"));
            out.flush();

            int read;
            while ((read = in.read()) >= 0) {
                String msg = endc.decodeNextByte((byte) read);
                if (msg != null) {
                    System.out.println(msg);
                }
            }
            out.write(endc.encode("Send\n" +
                    "destination:a"+"\n"+
                    "\n"+
                    "Book status"
                    +
                    "^@"));
            out.flush();
            System.out.println("awaiting response");


        }
    }
}
