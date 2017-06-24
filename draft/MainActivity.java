package com.example.hungpt.myapplication;

        import android.app.Notification;
        import android.app.NotificationManager;
        import android.app.PendingIntent;
        import android.content.Context;
        import android.content.Intent;
        import android.support.v4.app.NotificationCompat;
        import android.support.v7.app.AppCompatActivity;
        import android.os.Bundle;
        import android.app.Activity;
        import android.view.LayoutInflater;
        import android.view.View;
        import android.view.View.OnClickListener;
        import android.view.ViewGroup.LayoutParams;
        import android.widget.Button;
        import android.widget.EditText;
        import android.widget.LinearLayout;
        import android.widget.ListView;
        import android.widget.TextView;
        import android.widget.Toast;
import android.os.AsyncTask;
import android.util.Log;

        import java.util.ArrayList;


public class MainActivity extends AppCompatActivity {
    private ListView mList;
    private ArrayList<String> arrayList;
    private MyCustomAdapter mAdapter;
    private TCPClient mTcpClient;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        arrayList = new ArrayList<String>();

        final TextView textView = (TextView) findViewById(R.id.textView);

        //relate the listView from java to the one created in xml
        mList = (ListView)findViewById(R.id.list);
        mAdapter = new MyCustomAdapter(this, arrayList);
        mList.setAdapter(mAdapter);

        // connect to the server
        new connectTask().execute("");
        //textView.setText("Conecting...");
    }

    public class connectTask extends AsyncTask<String,String,TCPClient> {

        @Override
        protected TCPClient doInBackground(String... message) {

            //we create a TCPClient object and
            mTcpClient = new TCPClient ( new TCPClient.OnMessageReceived() {
                @Override
                //here the messageReceived method is implemented
                public void messageReceived(String message) {
                    //this method calls the onProgressUpdate
                    publishProgress(message);
                    mAdapter.notifyDataSetChanged();
                    //addNotification(message);
                }
            }/*, new TCPClient.OnTcpStatus() {
                        @Override
                        //here the messageReceived method is implemented
                        public void TcpStatus(String message) {
                            //this method calls the onProgressUpdate
//                            textView.setText(message);
                        }
                    }*/
            );
            mTcpClient.run();

            return null;
        }

        @Override
        protected void onProgressUpdate(String... values) {
            super.onProgressUpdate(values);

            //in the arrayList we add the messaged received from server
            arrayList.add(values[0]);
            // notify the adapter that the data set has changed. This means that new message received
            // from server was added to the list

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
