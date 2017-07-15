package com.example.hungpt.myapplication.service;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;
import android.util.Log;

import java.io.BufferedReader;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * Created by danhdueexoictif on 6/19/17.
 */

public class MyService extends AbstractService
{

    private Handler handler;
    private CheckingTimeRunnable checkingTimeRunnable;

    private String serverMessage;
    //    TextView viewStatus;
    public static final String SERVERIP = "192.168.1.222"; //your computer IP address
    public static final int SERVERPORT = 21;
    //    private TCPClient.OnMessageReceived mMessageListener = null;
    //private OnTcpStatus mTcpStatus = null;
    private boolean mRun = false;
    PrintWriter out;
    BufferedReader in;
    Socket socket;
    //private Handler handler;
//    private TCP_Client.TcpService tcpService;

    @Override
    public void onStartService()
    {
        checkCurrentTime();
    }

    @Override
    public void onStopService()
    {
        if (handler != null && checkingTimeRunnable != null)
        {
            handler.removeCallbacks(checkingTimeRunnable);
            checkingTimeRunnable = null;
            handler = null;
        }
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
        sendBroadcast(new Intent("com.danhdueexoictif.servicesample.RESTART_SERVICE"));
    }

    @Override
    public void onReceiveMessage(Message msg)
    {
        Log.e("MyService","got message");

    }

    @Override
    public void onTaskRemoved(Intent rootIntent)
    {
        Intent restartServiceTask = new Intent(getApplicationContext(),this.getClass());
        restartServiceTask.setPackage(getPackageName());
        PendingIntent restartPendingIntent =PendingIntent.getService(getApplicationContext(), 1,restartServiceTask, PendingIntent.FLAG_ONE_SHOT);
        AlarmManager myAlarmService = (AlarmManager) getApplicationContext().getSystemService(Context.ALARM_SERVICE);
        myAlarmService.set(
                AlarmManager.ELAPSED_REALTIME,
                SystemClock.elapsedRealtime() + 1000,
                restartPendingIntent);

        super.onTaskRemoved(rootIntent);
        sendBroadcast(new Intent("com.danhdueexoictif.servicesample.RESTART_SERVICE"));
    }

    private void checkCurrentTime()
    {
        handler = new Handler();
        checkingTimeRunnable = new CheckingTimeRunnable();
        handler.postDelayed(checkingTimeRunnable, 1000);
    }

    private class CheckingTimeRunnable implements Runnable
    {
        @Override
        public void run()
        {
            //Log.e("CheckingTimeRunnable", "Current time: " + System.currentTimeMillis());
            if (handler != null)
            {
                handler.postDelayed(this, 1000);
            }
        }
    }

}