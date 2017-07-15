package com.example.hungpt.myapplication;

        import android.app.Notification;
        import android.app.NotificationManager;
        import android.app.PendingIntent;
        import android.content.Context;
        import android.content.Intent;
        import android.os.CountDownTimer;
        import android.os.Handler;
        import android.os.Message;
        import android.os.RemoteException;
        import android.support.v4.app.NotificationCompat;
        import android.support.v7.app.AppCompatActivity;
        import android.os.Bundle;
        import android.view.View;
        import android.widget.EditText;
        import android.widget.ListView;
        import android.widget.TextView;

        import com.example.hungpt.myapplication.TCPService.TCP_Client;
        import com.example.hungpt.myapplication.service.MyService;
        import com.example.hungpt.myapplication.service.OnEventController;
        import com.example.hungpt.myapplication.service.ServiceManager;
import android.os.AsyncTask;
import android.util.Log;
        import android.widget.Toast;

        import java.util.ArrayList;
        import java.util.Timer;
        import java.util.TimerTask;


public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private ListView mList;
    Timer mCheckConnection;
    int mDisconnectTimes = 2;
    public TextView viewStatus;
    public String mStatus;
    private ArrayList<String> arrayList;
    private MyCustomAdapter mAdapter;
    private TCPClient mTcpClient;
    Context context = this;
    private ServiceManager serviceManager;

    //public static final int ACTIV_MSG_SHOW_MESSAGE = 1;
    //public static final int ACTIV_MSG_FINISH_ACTIVITY = 2;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        arrayList = new ArrayList<String>();

        //relate the listView from java to the one created in xml
        mList = (ListView)findViewById(R.id.list);
        //final TextView viewStatus = (TextView)findViewById(R.id.textView2);
        viewStatus = (TextView)findViewById(R.id.textView2);
        mAdapter = new MyCustomAdapter(context, arrayList);
        //mAdapter = new MyCustomAdapter(this, mStatus);

        mList.setAdapter(mAdapter);

        // connect to the server
//        new connectTask().execute(viewStatus);
        viewStatus.setText("Connecting...");
        mCheckConnection = new Timer();
        mCheckConnection.schedule(new TimerTask() {

            @Override
            public void run() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        if (mDisconnectTimes == 0) {
                            //mCheckConnection.cancel();
                            //mTcpClient.stopClient();
                            mDisconnectTimes = 3;
                            viewStatus.setText("No response from the server, reconnecting...");
                            //new connectTask().execute(viewStatus);
                        } else
                        {
                            if(mStatus == "Connected") {
                                Log.e("Timer", "Connected");
                                mStatus = "Disconnect";
                                mDisconnectTimes = 3;
                            }
                            else {
                                Log.e("Timer", "Disconnect");
                                viewStatus.setText("Disconnected (" + Integer.toString(mDisconnectTimes) + ")");
                                mDisconnectTimes--;
                            }
//                            if (mTcpClient != null)
//                                mTcpClient.sendMessage("Connection");
                        }
                    }
                });
            }
        }, 6000, 6000);

        serviceManager = new ServiceManager(this, MyService.class, new Handler()
        {
            @Override
            public void handleMessage(Message msg)
            {
                super.handleMessage(msg);

                switch (msg.what)
                {
                    case OnEventController.SERVICE_EVENT.MY_SERVICE_SHOW_MSG_SUCCESS:
                    {
                        Log.e("MainActivity", "MY_SERVICE_SHOW_MSG_SUCCESS");
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }

            }
        });

        serviceManager.start();
    }

    public class connectTask extends AsyncTask<TextView,String,TCPClient> {

        //final TextView viewStatus = (TextView)findViewById(R.id.textView2);
        @Override
        protected TCPClient doInBackground(final TextView ... viewStatus) {

            //we create a TCPClient object and
            mTcpClient = new TCPClient(new TCPClient.OnMessageReceived() {
                @Override
                //here the messageReceived method is implemented
                public void messageReceived(String message) {
                    //this method calls the onProgressUpdate
                    publishProgress(message);
                }
            });
            mTcpClient.run();

            return null;
        }

        @Override
        protected void onProgressUpdate(String... values) {
            super.onProgressUpdate(values);

            if (values[0].contains("OK")) {
                viewStatus.setText("Connected");
                mStatus = "Connected";
            }
            else {
                //in the arrayList we add the messaged received from server
                arrayList.add(values[0]);
                //mStatus = values[0];
                // notify the adapter that the data set has changed. This means that new message received
                // from server was added to the list
                mAdapter.notifyDataSetChanged();
                addNotification(values[0]);
            }
        }
    }

    @Override
    public void onClick(View v)
    {
        switch (v.getId())
        {
            case R.id.butFinishActivity:
            {
                sendMessage(OnEventController.ACTIVITY_EVENT.MAIN_AC_SHOW_MESSAGE);
                //finish();
                break;
            }
            default:
            {
                break;
            }
        }
    }
    private void sendMessage(int intValue2Send)
    {
        try
        {
            serviceManager.send(Message.obtain(null, intValue2Send, 0, 0));
        }
        catch (RemoteException e)
        {
            e.printStackTrace();
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

    @Override
    protected void onDestroy() {
        super.onDestroy();
        try
        {
            serviceManager.unbind();
        }
        catch (Throwable throwable)
        {
            Log.e(MainActivity.class.getName(), "Failed to unbind from the service", throwable);
        }

    }
}
