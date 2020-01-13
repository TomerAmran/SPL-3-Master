package bgu.spl.net.tests;

import bgu.spl.net.impl.stomp.StompFrame;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;

public class StompFrameTest {
    public static void main(String[] args) throws Exception {

        BufferedWriter output = null;
        try {
            File file = new File("example.txt");
            output = new BufferedWriter(new FileWriter(file));
            for (int i =1 ; i<10000; i++)
            output.write("status "+" topic1\n");
        } catch ( IOException e ) {
            e.printStackTrace();
        } finally {
            if (output != null) {
                output.close();
            }
        }
//        String m1 ="CONNECT\n" +
//                "accept-version:1.0,1.1,2.0\n" +
//                "host:stomp.github.org\n" +
//                "\n";
//        String m2 ="MESSAGE\n" +
//                "subscription:0\n" +
//                "message-id:007\n" +
//                "destination:/queue/a\n" +
//                "content-type:text/plain\n" +
//                "\n" +
//                "hello queue a";
//        String m3;
//        String m4;
//        StompFrame f1 = StompFrame.parse(m1);
//        StompFrame f2 = StompFrame.parse(m2);
//        System.out.println(f1.toString());
//        System.out.println(f2.toString());
//        String a = "aba";
//        String b = a+ '\u0000';
//        System.out.println(a.length());
//        System.out.println(b.length());
//        System.out.println(a);
//        System.out.println(b);

    }
}
