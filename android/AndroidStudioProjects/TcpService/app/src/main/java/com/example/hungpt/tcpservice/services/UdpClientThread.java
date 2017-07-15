package com.example.hungpt.tcpservice.services;

/**
 * Created by hungpt on 7/8/2017.
 */
import android.os.Message;

import com.example.hungpt.tcpservice.MainActivity;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

public class UdpClientThread{

    String dstAddress;
    int dstPort;
    String Data;
    private boolean running;

    DatagramSocket socket;
    InetAddress address;

    public UdpClientThread(String addr, int port, String data) {
        super();
        dstAddress = addr;
        dstPort = port;
        Data = data;
    }

    public void setRunning(boolean running){
        this.running = running;
    }


    public void send() {

        running = true;

        try {
            socket = new DatagramSocket();
            address = InetAddress.getByName(dstAddress);
            // send request
            byte buf[] = Data.getBytes();

            DatagramPacket packet =
                    new DatagramPacket(buf, buf.length, address, dstPort);
            socket.send(packet);


            // get response
            //packet = new DatagramPacket(buf, buf.length);


            //socket.receive(packet);
            //String line = new String(packet.getData(), 0, packet.getLength());


        } catch (SocketException e) {
            e.printStackTrace();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if(socket != null){
                socket.close();
            }
        }

    }
}
