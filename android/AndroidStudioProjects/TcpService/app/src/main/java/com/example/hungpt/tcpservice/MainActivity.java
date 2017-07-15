package com.example.hungpt.tcpservice;

import android.content.Context;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Handler;
import android.os.Message;
import android.os.RemoteException;
import android.os.StrictMode;
import android.support.annotation.IdRes;
import android.support.annotation.NonNull;
import android.support.constraint.ConstraintLayout;
import android.support.design.widget.BottomNavigationView;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.NavigationView;
import android.support.design.widget.Snackbar;
import android.support.design.widget.TabLayout;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.GravityCompat;
import android.support.v4.view.ViewPager;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.Switch;
import android.widget.TextView;

import com.example.hungpt.tcpservice.services.MyService;
import com.example.hungpt.tcpservice.manager.OnEventController;
import com.example.hungpt.tcpservice.manager.ServiceManager;
import com.example.hungpt.tcpservice.services.TCPClient;
import com.example.hungpt.tcpservice.services.UdpClientThread;
import com.example.hungpt.tcpservice.setting.SettingsActivity;
import com.example.hungpt.tcpservice.setting.AppCompatPreferenceActivity;
import com.example.hungpt.tcpservice.views.TabPageView;

import java.text.CollationElementIterator;
import java.util.ArrayList;
import java.util.Objects;

import static com.example.hungpt.tcpservice.R.menu.navigation;

public class MainActivity extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener
{
    private ServiceManager serviceManager;

    public static final int ACTIV_MSG_SHOW_MESSAGE = 1;
    public static final int ACTIV_MSG_FINISH_ACTIVITY = 2;
    public TabLayout tabLayout;
    private TextView tvHelloWorld;
    private Button butFinishActivity;
    private TextView mTextMessage;
    private TabPageView mtabPageViews;

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            Intent intent = new Intent(MainActivity.this, SettingsActivity.class);
            startActivity(intent);
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_navigation_drawer);
        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.setDrawerListener(toggle);
        toggle.syncState();

        // Set up the ViewPager with the sections adapter.
        mtabPageViews = new TabPageView();
        mtabPageViews.mViewPager = (ViewPager) findViewById(R.id.container);
        mtabPageViews.tabLayout = (TabLayout) findViewById(R.id.room_tabs);

        mtabPageViews.onStartView(getSupportFragmentManager());
        //startView(tabLayout);

        serviceManager = new ServiceManager(this, MyService.class, new Handler()
        {
            @Override
            public void handleMessage(Message msg)
            {
                Log.e("MainActivity", "Message from service");
                Bundle data = msg.getData();
                mtabPageViews.processData(data.getString("string_data"));
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
        sendMessage(OnEventController.ACTIVITY_EVENT.MAIN_AC_SHOW_MESSAGE);
    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }
    public boolean onNavigationItemSelected(MenuItem item) {
        // Handle navigation view item clicks here.
        int id = item.getItemId();

        if (id == R.id.nav_lights) {
            sendMessage(OnEventController.ACTIVITY_EVENT.MAIN_AC_SHOW_MESSAGE);
        } else if (id == R.id.nav_scene) {
            sendMessage(OnEventController.ACTIVITY_EVENT.MAIN_AC_SHOW_MESSAGE);
        } else if (id == R.id.nav_camera) {
            sendMessage(OnEventController.ACTIVITY_EVENT.MAIN_AC_SHOW_MESSAGE);
        } else if (id == R.id.nav_tv) {
            mtabPageViews.deviceView(0);
        } else if (id == R.id.nav_digibox) {
            mtabPageViews.deviceView(1);
        } else if (id == R.id.nav_ac) {
            mtabPageViews.deviceView(2);
        } else if (id == R.id.nav_fan) {
            mtabPageViews.deviceView(3);
        }

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
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
    /**
     * A placeholder fragment containing a simple view.
     */

    public void createArraySwitch(){

    }
}