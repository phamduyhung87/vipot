package com.example.hungpt.myapplication.service;

import android.app.ActivityManager;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

/**
 * Created by danhdueexoictif on 6/24/17.
 */

public enum TestServiceUtils
{
    INSTANCE;

    private Context context;

    public static TestServiceUtils getInstance(Context context)
    {
        INSTANCE.context = context;
        return INSTANCE;
    }

    public boolean isMyServiceRunning(Class<?> serviceClass)
    {
        ActivityManager manager = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
        for (ActivityManager.RunningServiceInfo service : manager.getRunningServices(Integer.MAX_VALUE))
        {
            if (serviceClass.getName().equals(service.service.getClassName()))
            {
                Log.e("isMyServiceRunning?", true + "");
                return true;
            }
        }
        Log.e("isMyServiceRunning?", false + "");
        return false;
    }

    public void startService()
    {
        Intent intent = new Intent(context, MyService.class);
        context.startService(intent);
    }
}