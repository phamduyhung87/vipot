package com.example.hungpt.tcpservice.views;

import android.os.Bundle;
import android.os.StrictMode;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import android.widget.LinearLayout;
import android.widget.Switch;
import android.widget.TextView;

import com.example.hungpt.tcpservice.R;
import com.example.hungpt.tcpservice.services.TCPClient;

/**
 * Created by hungpt on 7/10/2017.
 */

public class TvFragment extends Fragment {
    /**
     * The fragment argument representing the section number for this
     * fragment.
     */
    private TCPClient mTcpClient;
    private static final String ARG_SECTION_NUMBER = "section_number";
    private static final String LIGHTS = "section_switch_name";
    private static final String PAGE = "section_page";

    public TvFragment() {
    }

    /**
     * Returns a new instance of this fragment for the given section
     * number.
     */
    public static TvFragment newInstance(int sectionNumber, String[] sectionCharSequence, int sectionPage) {
        TvFragment fragment = new TvFragment();
        Bundle args = new Bundle();
        args.putInt(ARG_SECTION_NUMBER, sectionNumber);
        args.putCharSequenceArray(LIGHTS, sectionCharSequence);
        args.putInt(PAGE, sectionPage);
        fragment.setArguments(args);
        return fragment;
    }
    /*String switchName[][] = {   {"Den Bep","Hanh Lang","Ban Cong","Nha Bep"},
            {"San Thuong","Ban Cong","Nha Bep"},
            {"Down Light","Hanh Lang","Ban Cong","Nha Bep"},
            {"Den Bep","Hanh Lang","Ban Cong","Nha Bep"},
            {"Den Bep","Hanh Lang","Ban Cong","Nha Bep"},
            {"Den Bep","Hanh Lang","Ban Cong","Nha Bep"}};*/
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.remote_fan_layout, container, false);
        if (android.os.Build.VERSION.SDK_INT > 9)
        {
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
            StrictMode.setThreadPolicy(policy);
        }
        return rootView;
    }
    public boolean onCheck(String c){
        Log.e ("Check", c);
        if (c.endsWith("a")||c.endsWith("b")||c.endsWith("c"))
            return true;
        else
            return false;
    }
    private void LightView (View rootView, LinearLayout linearLayout){
        int n = getArguments().getInt(ARG_SECTION_NUMBER) - 1;
        String strings[] = getArguments().getStringArray(LIGHTS);
        CharSequence switchName[] = strings[n].split(";");
        for (int i = 0; i < switchName.length; i++){
            Switch switchView = new Switch(rootView.getContext());
            String string[] = ((String) switchName[i]).split("::");
            //switchView.setId(R.id.switch_view);
            switchView.setText(string[0]);
            switchView.setTextSize(20);
            switchView.setHint(string[1]);
            switchView.setChecked(onCheck(string[1]));
            switchView.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                    // do something, the isChecked will be
                    // true if the switch is in the On position
                    Log.e("Switch Press", (String) buttonView.getHint());
                    //UdpClientThread udpClient = new UdpClientThread("192.168.1.22",12345,"rf " + (String) buttonView.getHint());
                    //udpClient.send();
                    TCPClient tcpClient = new TCPClient(null);
                    tcpClient.SERVERIP = "192.168.1.30";
                    tcpClient.SERVERPORT = 80;
                    tcpClient.sendTcpMessage("POST /sendrf-" + (String) buttonView.getHint() +" HTTP/1.1");

                }
            });
            linearLayout.addView(switchView);
        }
    }

}

