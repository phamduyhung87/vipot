package com.example.hungpt.tcpservice.services;

import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;
import android.preference.PreferenceManager;
import android.support.annotation.NonNull;
import android.support.design.widget.BottomNavigationView;
import android.support.design.widget.TabLayout;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.app.NotificationCompat;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import java.net.URL;
import java.util.Timer;
import java.util.TimerTask;

import com.example.hungpt.tcpservice.MainActivity;
import com.example.hungpt.tcpservice.R;
import com.example.hungpt.tcpservice.manager.AbstractService;
import com.example.hungpt.tcpservice.manager.OnEventController;

import java.io.BufferedReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Timer;
import java.util.TimerTask;

/**
 * Created by danhdueexoictif on 6/19/17.
 */

public class MyService extends AbstractService
{

    /**
     * The {@link android.support.v4.view.PagerAdapter} that will provide
     * fragments for each of the sections. We use a
     * {@link FragmentPagerAdapter} derivative, which will keep every
     * loaded fragment in memory. If this becomes too memory intensive, it
     * may be best to switch to a
     * {@link android.support.v4.app.FragmentStatePagerAdapter}.
     */
    //private MainActivity.SectionsPagerAdapter mSectionsPagerAdapter;

    /**
     * The {@link ViewPager} that will host the section contents.
     */
    private ViewPager mViewPager;

    private Handler handler;

    public TCPClient mTcpClient;
    Timer mCheckConnection;
    int mDisconnectTimes = 2;
    public TextView viewStatus;
    public String mStatus;
    Toast toast;
    String server_ip;
    public Integer tcp_port;
    Integer udp_port;

    public String sLights = "room: P Khach;P Ngu;Bep;Van Phong\n" +
            "light: 1;bat default;abcdef;a;a;1;1;Tivi;abcdef;A;a;1;1;hung;abcdef;b;a;1;2;tuan 3;tuan01;c;a;1;2;tuan 1;tuan01;B;a;1;3;tuan 2;tuan01;C;a;1;4;tat default;undefined;C;a;1;1;tuan 2;tuan02;b;a;1\n" +
            "scene: Bat;Tat;Bat het;Tat het\n" +
            "remote: 1111;s;l;p;1;2222;d;a;m;1;3333;m;n;a;1;;s;s";

    public CharSequence RoomName[] = {"Room 1","Room 2","Room 3","Room 4","Room 5"};
    public CharSequence DeviceName[] = {"- TV -","DigiBox","- A/C -","Fan"};
    public CharSequence TabName[];
    String switchName[] = {"","","","","",""};



    //private Handler handler;
//    private TCP_Client.TcpService tcpService;

    @Override
    public void onStartService()
    {

        LayoutInflater inflater = (LayoutInflater) getSystemService(LAYOUT_INFLATER_SERVICE);
        View layout = inflater.inflate(R.layout.service_layout, null);
        viewStatus = (TextView) layout.findViewById(R.id.viewStatus) ;
        toast = new Toast(getApplicationContext());
        toast.setGravity(Gravity.BOTTOM, 0, 0);
        toast.setDuration(Toast.LENGTH_LONG);
        toast.setView(layout);

        SharedPreferences settings = PreferenceManager.getDefaultSharedPreferences(this);
        server_ip = settings.getString("example_text","n/a");
        try {server_ip = new URL(server_ip).getHost();} catch (Exception e) {Log.e("URL Exception", server_ip);}
        //Log.e("URL server ip", server_ip);
        //server_ip = url;
        String s_tcp_port = settings.getString("edit_text_preference_1","n/a");

        tcp_port = Integer.parseInt(s_tcp_port);
        String s_udp_port = settings.getString("edit_text_preference_2","n/a");
        udp_port = Integer.parseInt(s_tcp_port);
        Log.e("TCP SERVER IP",server_ip);
        Log.e("TCP PORT",Integer.toString(tcp_port));

        new connectTask().execute(server_ip);
        checkConnection();
        viewStatus.setText("Connecting");
        toast.show();
    }

    @Override
    public void onStopService()
    {
        if (handler != null)
        {
            handler = null;
        }
        if (mTcpClient != null){
            mTcpClient.stopClient();
        }
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
        if (mTcpClient != null){
            mTcpClient.stopClient();
        }

        sendBroadcast(new Intent("com.danhdueexoictif.servicesample.RESTART_SERVICE"));
    }

    @Override
    public void onReceiveMessage(Message msg)
    {
        Log.e("MyService","got message");
        switch (msg.what){
            case OnEventController.ACTIVITY_EVENT.MAIN_AC_SHOW_MESSAGE:
            {
                mTcpClient.sendMessage("lights");
                break;
            }
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

    public class connectTask extends AsyncTask<String,String,TCPClient> {

        //final TextView viewStatus = (TextView)findViewById(R.id.textView2);
        @Override
        protected TCPClient doInBackground(final String... server_ip) {

            //we create a TCPClient object and
            mTcpClient = new TCPClient(new TCPClient.OnMessageReceived() {
                @Override
                //here the messageReceived method is implemented
                public void messageReceived(String message) {
                    //this method calls the onProgressUpdate
                    publishProgress(message);
                }
            });
            mTcpClient.SERVERIP = server_ip[0];
            mTcpClient.SERVERPORT = tcp_port;
            mTcpClient.run();

            return null;
        }

        @Override
        protected void onProgressUpdate(String... values) {
            super.onProgressUpdate(values);
//            if (socket.isConnected())
                Log.e("TCP Message:",values[0]);
  //          else
//                Log.e("TCP Client", "C: Disconnected.");

            if (values[0].startsWith("Unknow request!")) {
                Log.e("Service","Connected to the server");
                mStatus = "Connected";
            }
            else {
                Message msg = new Message();
                Bundle data = new Bundle();
                data.putString("string_data",values[0]);
                msg.setData(data);
                send(msg);
                //addNotification(values[0]);
            }
        }
    }
    private void addNotification(String message) {
        NotificationCompat.Builder builder =
                new NotificationCompat.Builder(this)
                        .setSmallIcon(R.drawable.abc)
                        .setContentTitle("Notifications Example")
                        .setContentText(message);
        builder.setDefaults(Notification.DEFAULT_SOUND);
        Intent notificationIntent = new Intent(this, MainActivity.class);
        PendingIntent contentIntent = PendingIntent.getActivity(this, 0, notificationIntent,
                PendingIntent.FLAG_UPDATE_CURRENT);
        builder.setContentIntent(contentIntent);

        // Add as notification
        NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        manager.notify(0, builder.build());
    }

    public void checkConnection(){

        mCheckConnection = new Timer();
        mCheckConnection.schedule(new TimerTask() {

                                       @Override
                                       public void run() {
                                           if (mDisconnectTimes == 0) {
                                               //mCheckConnection.cancel();
                                               mTcpClient.stopClient();
                                               mDisconnectTimes = 2;
                                               Log.e("Timer","No response from the server, reconnecting...");
                                               viewStatus.setText("No response from the server, reconnecting...");
                                               toast.show();
                                               new connectTask().execute(server_ip);
                                           } else
                                           {
                                               if(mStatus == "Connected") {
                                                   Log.e("Timer", "Connected");
                                                   mStatus = "Disconnect";
                                                   mDisconnectTimes = 2;
                                               }
                                               else {
                                                   Log.e("Timer", "Disconnect " + Integer.toString(mDisconnectTimes));
                                                   viewStatus.setText("Disconnected (" + Integer.toString(mDisconnectTimes) + ")");
                                                   mDisconnectTimes--;
                                               }
                                               if (mTcpClient != null)
                                                   mTcpClient.sendMessage("Connection");
                                           }
                                       }

                                   }, 15000, 15000);
    }
    public void TcpConnect(String server_ip) {
        new connectTask().execute(server_ip);
    }
}