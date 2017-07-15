package com.example.hungpt.tcpservice.manager;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.example.hungpt.tcpservice.services.MyService;


/**
 * Created by danhdueexoictif on 6/24/17.
 */

public class MyBroadcastReceiver extends BroadcastReceiver
{
    @Override
    public void onReceive(Context context, Intent intent)
    {
        if (intent.getAction().equalsIgnoreCase(Intent.ACTION_BOOT_COMPLETED))
        {
            Log.e("MyBroadcastReceiver", "ACTION_BOOT_COMPLETED");
            Intent serviceIntent = new Intent(context, MyService.class);
            context.startService(serviceIntent);
        }
        if (intent.getAction().equalsIgnoreCase("com.danhdueexoictif.servicesample.RESTART_SERVICE"))
        {
            Log.e("MyBroadcastReceiver", "com.danhdueexoictif.servicesample.RESTART_SERVICE");
            if (!TestServiceUtils.getInstance(context).isMyServiceRunning(MyService.class))
            {
                TestServiceUtils.getInstance(context).startService();
            }
        }
    }
}