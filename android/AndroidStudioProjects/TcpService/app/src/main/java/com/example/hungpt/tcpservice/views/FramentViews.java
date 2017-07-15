package com.example.hungpt.tcpservice.views;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import com.example.hungpt.tcpservice.MainActivity;
import com.example.hungpt.tcpservice.R;

/**
 * Created by hungpt on 7/10/2017.
 */

public class FramentViews extends MainActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        setContentView(R.layout.remote_fan_layout);
        Log.e("Fragment View","Created");
    }
    public void start(){
        Log.e("Fragment View","Start");
        setContentView(R.layout.remote_fan_layout);
    }
}
