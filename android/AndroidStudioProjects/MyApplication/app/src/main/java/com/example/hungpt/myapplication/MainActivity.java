package com.example.hungpt.myapplication;

        import android.app.Notification;
        import android.app.NotificationManager;
        import android.app.PendingIntent;
        import android.content.Context;
        import android.content.Intent;
        import android.os.CountDownTimer;
        import android.support.v4.app.NotificationCompat;
        import android.support.v7.app.AppCompatActivity;
        import android.os.Bundle;
        import android.widget.EditText;
        import android.widget.ListView;
        import android.widget.TextView;

import android.os.AsyncTask;
import android.util.Log;
        import android.widget.Toast;

        import java.util.ArrayList;
        import java.util.Timer;
        import java.util.TimerTask;


public class MainActivity extends AppCompatActivity {
    private ListView mList;
    Timer mCheckConnection;
    int mDisconnectTimes = 2;
    public TextView viewStatus;
    public String mStatus;
    private ArrayList<String> arrayList;
    private MyCustomAdapter mAdapter;
    private TCPClient mTcpClient;
    Context context = this;
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        arrayList = new ArrayList<String>();

        //final TextView editText = (TextView) findViewById(R.id.textView);
        //Button send = (Button)findViewById(R.id.send_button);

        //relate the listView from java to the one created in xml
        mList = (ListView)findViewById(R.id.list);
        //final TextView viewStatus = (TextView)findViewById(R.id.textView2);
        viewStatus = (TextView)findViewById(R.id.textView2);
        mAdapter = new MyCustomAdapter(context, arrayList);
        //mAdapter = new MyCustomAdapter(this, mStatus);

        mList.setAdapter(mAdapter);

        // connect to the server
        new connectTask().execute(viewStatus);
        viewStatus.setText("Connecting...");
        /*send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                String message = editText.getText().toString();

                //add the text in the arrayList
                arrayList.add("c: " + message);

                //sends the message to the server
                if (mTcpClient != null) {
                    mTcpClient.sendMessage(message);
                }

                //refresh the list
                mAdapter.notifyDataSetChanged();
                editText.setText("");
            }
        });*/
        mCheckConnection = new Timer();
        mCheckConnection.schedule(new TimerTask() {

            @Override
            public void run() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        if (mDisconnectTimes == 0) {
                            //mCheckConnection.cancel();
                            mTcpClient.stopClient();
                            mDisconnectTimes = 3;
                            viewStatus.setText("No response from the server, reconnecting...");
                            new connectTask().execute(viewStatus);
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
                            if (mTcpClient != null)
                                mTcpClient.sendMessage("Connection");
                        }
                    }
                });
            }
        }, 6000, 6000);

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
}
