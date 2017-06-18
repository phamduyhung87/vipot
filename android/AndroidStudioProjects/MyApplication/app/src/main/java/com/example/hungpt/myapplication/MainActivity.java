package com.example.hungpt.myapplication;

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
        import android.widget.TextView;
        import android.widget.Toast;
import android.os.AsyncTask;
import android.util.Log;


public class MainActivity extends AppCompatActivity {
    TcpClient mTcpClient;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        LinearLayout layout = (LinearLayout) findViewById(R.id.layout);
        final EditText textInput = new EditText(this);
        final TextView textOutput = new TextView(this);
        textInput.setText("input");
        layout.addView(textInput);
        for (int i = 0; i < 4; i++) {
            Button myButton = new Button(this);
            myButton.setText("Button :"+i);
            myButton.setId(i);
            final int id_ = myButton.getId();

            layout.addView(myButton);

            myButton.setOnClickListener(new View.OnClickListener() {
                public void onClick(View view) {
                    //Toast.makeText(DynamicLayout.this,"Button clicked index = " + id_, Toast.LENGTH_SHORT).show();
                    String text = textOutput.getText() + "" + textInput.getText() + id_ + "\n";
                    textOutput.setText(text);
                    new ConnectTask().execute("");
                    if (mTcpClient != null) {
                        mTcpClient.sendMessage("testing");
                    }
                }
            });
        }
        textOutput.setText("");
        layout.addView(textOutput);
    }
    public class ConnectTask extends AsyncTask<String, String, TcpClient> {

        @Override
        protected TcpClient doInBackground(String... message) {

            //we create a TCPClient object
            mTcpClient = new TcpClient(new TcpClient.OnMessageReceived() {
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
            //response received from server
            Log.d("test", "response " + values[0]);
            //process server response here....

        }
    }
}
