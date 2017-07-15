package com.example.hungpt.myapplication.TCPService;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;
import android.util.Log;
import android.widget.TextView;

import com.example.hungpt.myapplication.TCPClient;
import com.example.hungpt.myapplication.service.AbstractService;
import com.example.hungpt.myapplication.service.MyService;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

/**
 * Created by hungpt on 6/25/2017.
 */

public class TCP_Client extends AbstractService {
    Context context;
    private String serverMessage;
    TextView viewStatus;
    public static final String SERVERIP = "192.168.1.222"; //your computer IP address
    public static final int SERVERPORT = 21;
    private TCPClient.OnMessageReceived mMessageListener = null;
    //private OnTcpStatus mTcpStatus = null;
    private boolean mRun = false;
    PrintWriter out;
    BufferedReader in;
    Socket socket;
    private Handler handler;
    private TCP_Client.TcpService tcpService;


    /**
     *  Constructor of the class. OnMessagedReceived listens for the messages received from server
     */
//    public TCPClient(TCPClient.OnMessageReceived listener) {
//        mMessageListener = listener;
//    }

    /**
     * Sends the message entered by client to the server
     * @param message text entered by client
     */
    public void sendMessage(String message){
        if (out != null && !out.checkError()) {
            out.println(message);
            out.flush();
        }
    }

    @Override
    public void onStartService()
    {
        checkCurrentTime();
    }

    private void checkCurrentTime()
    {
        handler = new Handler();
        tcpService = new TCP_Client.TcpService();
        handler.post(tcpService);
    }
    private class TcpService implements Runnable
    {
        @Override
        public void run() {

        }
    }
    public interface OnMessageReceived {
        public void messageReceived(String message);
    }


    @Override
    public void onStopService()
    {
        try {
            socket.close();
        } catch (Exception e) {}
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        sendBroadcast(new Intent("com.danhdueexoictif.servicesample.RESTART_SERVICE"));
        try {
            socket.close();
        } catch (Exception e) {}
    }

    @Override
    public void onReceiveMessage(Message msg)
    {
        mRun = true;
        try {
            //here you must put your computer's IP address.
            InetAddress serverAddr = InetAddress.getByName(SERVERIP);

            Log.e("TCP Client", "C: Connecting...");
            //mTcpStatus.TcpStatus("Connected");
            //create a socket to make the connection with the server
            socket = new Socket(serverAddr, SERVERPORT);

            try {

                //send the message to the server
                out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);

                Log.e("TCP Client", "C: Sent.");

                Log.e("TCP Client", "C: Done.");

                //receive the message which the server sends back
                in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

                //in this while the client listens for the messages sent by the server
                while (mRun) {
                    if (socket.isConnected())
                        Log.e("TCP Client", "Connection: ");
                    else
                        Log.e("TCP Client", "C: Disconnected.");
                    serverMessage = in.readLine();

                    if (serverMessage != null && mMessageListener != null) {
                        //mMessageListener.messageReceived(serverMessage);
                    }
                    serverMessage = null;

                }

                Log.e("RESPONSE FROM SERVER", "S: Received Message: '" + serverMessage + "'");

            } catch (Exception e) {

                Log.e("TCP", "S: Error", e);

            } finally {
                //the socket must be closed. It is not possible to reconnect to this socket
                // after it is closed, which means a new socket instance has to be created.
                socket.close();
            }

        } catch (Exception e) {

            Log.e("TCP", "C: Error", e);

        }
    }

    @Override
    public void onTaskRemoved(Intent rootIntent)
    {
        Intent restartServiceTask = new Intent(getApplicationContext(),this.getClass());
        restartServiceTask.setPackage(getPackageName());
        PendingIntent restartPendingIntent = PendingIntent.getService(getApplicationContext(), 1,restartServiceTask, PendingIntent.FLAG_ONE_SHOT);
        AlarmManager myAlarmService = (AlarmManager) getApplicationContext().getSystemService(Context.ALARM_SERVICE);
        myAlarmService.set(
                AlarmManager.ELAPSED_REALTIME,
                SystemClock.elapsedRealtime() + 1000,
                restartPendingIntent);

        super.onTaskRemoved(rootIntent);
        sendBroadcast(new Intent("com.danhdueexoictif.servicesample.RESTART_SERVICE"));
    }
}
