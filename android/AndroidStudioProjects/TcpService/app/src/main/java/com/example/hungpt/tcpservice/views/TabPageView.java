package com.example.hungpt.tcpservice.views;

import android.os.Bundle;
import android.os.StrictMode;
import android.support.annotation.NonNull;
import android.support.design.widget.TabLayout;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.app.FragmentTransaction;
import android.support.v4.view.ViewPager;
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

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

/**
 * Created by hungpt on 7/9/2017.
 */

public class TabPageView {
    public int mPageType;
    FragmentManager mFragmentManager;
    FragmentTransaction mCurTransaction;
    Fragment mSavedState[];
    Fragment mFragments[];
    public String sLights = "room: P Khach;P Ngu;Bep;Van Phong\n" +
            "light: 1;bat default;abcdef;a;a;1;1;Tivi;abcdef;A;a;1;1;hung;abcdef;b;a;1;2;tuan 3;tuan01;c;a;1;2;tuan 1;tuan01;B;a;1;3;tuan 2;tuan01;C;a;1;4;tat default;undefined;C;a;1;1;tuan 2;tuan02;b;a;1\n" +
            "scene: Bat;Tat;Bat het;Tat het\n" +
            "remote: 1111;s;l;p;1;2222;d;a;m;1;3333;m;n;a;1;;s;s";

    public CharSequence RoomName[] = {"All","Room 1","Room 2","Room 3","Room 4","Room 5"};
    public CharSequence RoomTabs[] = {"All","Room 1","Room 2","Room 3","Room 4","Room 5"};
    public CharSequence DeviceTabs[] = {"- TV -","DigiBox","- A/C -","Fan"};
    public CharSequence TabName[];
    public String switchName[] = {"","","","","",""};
    public int[] countOnStatus = new int[6];
    String rfComand[] = {"","","","","",""};/*{   "Den Bep;Hanh Lang;Ban Cong;Nha Bep",
            "San Thuong;Ban Cong;Nha Bep",
            "Down Light;Hanh Lang;Ban Cong;Nha Bep",
            "Den Bep;Hanh Lang;Ban Cong;Nha Bep",
            "Den Bep;Hanh Lang;Ban Cong;Nha Bep",
            "Den Bep;Hanh Lang;Ban Cong;Nha Bep"};*/
    public boolean onCheck(String c){
        Log.e ("Check", c);
        if (c.endsWith("a")||c.endsWith("b")||c.endsWith("c"))
            return true;
        else
            return false;
    }
    public void processData(String data){
        boolean dataChanged = false;
        if (data.startsWith("room: ")){
            data = data.replace("room: ","All;");
            RoomName = data.replace("room: ","").split(";");
            RoomTabs = data.replace("room: ","").split(";");
            dataChanged = true;
        }
        if (data.startsWith("light: ")){
            String slights[] = data.replace("light: ", "").split(";");
            Log.e("Data light",data);
            int iCollum = 6;
            int iRoom = 0;
            int iLight = 1;
            int iCommand = 2;
            //switchName = new String[4];
            for (int i = 0; i < RoomName.length; i++){
                switchName[i] = "";
                countOnStatus[i] = 0;
            }

            for (int i = 0; i < (slights.length)/iCollum; i++){
                int r = Integer.parseInt(slights[i*iCollum + iRoom]) - 1;
                Log.e("Data switch",slights[i*iCollum + iLight]);
                String stringSwitch = slights[i*iCollum + iLight] + "::" + slights[i*iCollum + iCommand] + slights[i*iCollum + iCommand + 1];
                switchName[r + 1] += stringSwitch + ";";
                switchName[0] += stringSwitch + ";";
                if (onCheck(stringSwitch)) {
                    countOnStatus[r + 1] += 1;
                    countOnStatus[0] += 1;
                }
            }
            dataChanged = true;
        }
        for (int i = 0; i < RoomName.length; i ++){
            RoomTabs[i] = RoomName[i] + " (" + Integer.toString(countOnStatus[i]) + ")";
        }
        if (dataChanged)
            startView();
    }
    public void makeData(){
        Log.e("Data","Start Data");
        String strings[] = sLights.split("\n");
        RoomName = strings[0].replace("room: ", "").split(";");
        String slights[] = strings[1].replace("light: ", "").split(";");
        Log.e("Data slight",strings[1]);
        int iCollum = 6;
        int iRoom = 0;
        int iLight = 1;
        int iCommand = 2;
        //switchName = new String[4];
        for (int i = 0; i < (slights.length)/iCollum; i++){
            int r = Integer.parseInt(slights[i*iCollum + iRoom]) - 1;
            Log.e("Data switch",slights[i*iCollum + iLight]);
            switchName[r] += slights[i*iCollum + iLight] + "::" + slights[i*iCollum + iCommand] + slights[i*iCollum + iCommand + 1] + ";";
        }
        for (int i = 0; i < RoomName.length; i++){
            Log.e("Data switchName", switchName[i]);
        }
    }

    /**
     * The {@link android.support.v4.view.PagerAdapter} that will provide
     * fragments for each of the sections. We use a
     * {@link FragmentPagerAdapter} derivative, which will keep every
     * loaded fragment in memory. If this becomes too memory intensive, it
     * may be best to switch to a
     * {@link android.support.v4.app.FragmentStatePagerAdapter}.
     */
    public SectionsPagerAdapter mSectionsPagerAdapter;

    /**
     * The {@link ViewPager} that will host the section contents.
     */
    public ViewPager mViewPager;
    public TabLayout tabLayout;

    public void startView(){
        int possition = tabLayout.getSelectedTabPosition();
        TabName = RoomTabs;
        //mSectionsPagerAdapter.destroyItem(mViewPager,possition,mSectionsPagerAdapter.instantiateItem(mViewPager,possition));
        //mSectionsPagerAdapter.destroyAllItem();
        mViewPager.setAdapter(mSectionsPagerAdapter);
        //tabLayout.setScrollPosition(2,1,false);
        mPageType = 0;
        List<Fragment> listFragments = mFragmentManager.getFragments();
        Log.e("Fragment start", Integer.toString(mFragmentManager.getFragments().size()));
        FragmentTransaction fragmentTransaction = mFragmentManager.beginTransaction();
        fragmentTransaction.remove(listFragments.get(0));
        fragmentTransaction.detach(listFragments.get(1));
        Log.e("Fragment start", Integer.toString(mFragmentManager.getFragments().size()));
        tabLayout.setupWithViewPager(mViewPager);
        mViewPager.setCurrentItem(possition);
    }
    public void updateView(int possion){

        mViewPager.setCurrentItem(possion);
    }

    public void deviceView(int possition){
        Log.e("Device view", Integer.toString(possition));
        mPageType = 1;
        TabName = DeviceTabs;
        mViewPager.setAdapter(mSectionsPagerAdapter);
        //tabLayout.setScrollPosition(2,1,false);
        tabLayout.setupWithViewPager(mViewPager);
        mViewPager.setCurrentItem(possition);
        mViewPager.removeAllViews();
    }


    public void onStartView(FragmentManager fm){
        makeData();
        mFragmentManager = fm;
        TabName = RoomTabs;
        mSectionsPagerAdapter = new SectionsPagerAdapter(mFragmentManager);
    }



    /**
     * A {@link FragmentPagerAdapter} that returns a fragment corresponding to
     * one of the sections/tabs/pages.
     */
    public class SectionsPagerAdapter extends FragmentPagerAdapter {

        public SectionsPagerAdapter(FragmentManager fm) {
            super(fm);
        }

        @Override
        public Fragment getItem(int position) {
            // getItem is called to instantiate the fragment for the given page.
            // Return a PlaceholderFragment (defined as a static inner class below).
            if (mPageType == 0)
                return PlaceholderFragment.newInstance(position, switchName, mPageType);
            else{
                switch (position){
                    case 0:
                        return TvFragment.newInstance(position, switchName, mPageType);
                    case 1:
                        return TvFragment.newInstance(position, switchName, mPageType);
                    case 2:
                        return TvFragment.newInstance(position, switchName, mPageType);
                    case 3:
                        return TvFragment.newInstance(position, switchName, mPageType);
                    default:
                        return TvFragment.newInstance(position, switchName, mPageType);
                }
            }

        }

        @Override
        public int getCount() {
            // Show 3 total pages.
            return TabName.length;
        }

        @Override
        public CharSequence getPageTitle(int position) {
            if (position < TabName.length)
                return TabName[position];
            else
                return null;
        }
        List<Integer> TABLE = new List<Integer>() {
            @Override
            public int size() {
                return 0;
            }

            @Override
            public boolean isEmpty() {
                return false;
            }

            @Override
            public boolean contains(Object o) {
                return false;
            }

            @NonNull
            @Override
            public Iterator<Integer> iterator() {
                return null;
            }

            @NonNull
            @Override
            public Object[] toArray() {
                return new Object[0];
            }

            @NonNull
            @Override
            public <T> T[] toArray(@NonNull T[] ts) {
                return null;
            }

            @Override
            public boolean add(Integer integer) {
                return false;
            }

            @Override
            public boolean remove(Object o) {
                return false;
            }

            @Override
            public boolean containsAll(@NonNull Collection<?> collection) {
                return false;
            }

            @Override
            public boolean addAll(@NonNull Collection<? extends Integer> collection) {
                return false;
            }

            @Override
            public boolean addAll(int i, @NonNull Collection<? extends Integer> collection) {
                return false;
            }

            @Override
            public boolean removeAll(@NonNull Collection<?> collection) {
                return false;
            }

            @Override
            public boolean retainAll(@NonNull Collection<?> collection) {
                return false;
            }

            @Override
            public void clear() {

            }

            @Override
            public Integer get(int i) {
                return null;
            }

            @Override
            public Integer set(int i, Integer integer) {
                return null;
            }

            @Override
            public void add(int i, Integer integer) {

            }

            @Override
            public Integer remove(int i) {
                return null;
            }

            @Override
            public int indexOf(Object o) {
                return 0;
            }

            @Override
            public int lastIndexOf(Object o) {
                return 0;
            }

            @Override
            public ListIterator<Integer> listIterator() {
                return null;
            }

            @NonNull
            @Override
            public ListIterator<Integer> listIterator(int i) {
                return null;
            }

            @NonNull
            @Override
            public List<Integer> subList(int i, int i1) {
                return null;
            }
        };
        public void destroyAllItem() {
            TABLE.clear();
            for (int i = 0; i < mFragmentManager.getFragments().size(); i ++)
                TABLE.add(i);
            int mPosition = mViewPager.getCurrentItem();
            int mPositionMax = mPosition+1;
            if ((TABLE.size() > 0) && (mPosition < TABLE.size())) {
                if (mPosition > 0) {
                    mPosition--;
                }

                for (int i = mPosition; i < mPositionMax; i++) {
                    try {
                        Object objectobject = this.instantiateItem(mViewPager, TABLE.get(i).intValue());
                        if (objectobject != null)
                            destroyItem(mViewPager, TABLE.get(i).intValue(), objectobject);
                    } catch (Exception e) {
                        Log.i("Fragment remove", "no more Fragment in FragmentPagerAdapter");
                    }
                }
            }
        }

/*        @Override
        public void destroyItem(ViewGroup container, int position, Object object) {
            super.destroyItem(container, position, object);

            if (position <= getCount()) {
                FragmentManager manager = ((Fragment) object).getFragmentManager();
                FragmentTransaction trans = manager.beginTransaction();
                trans.remove((Fragment) object);
                trans.commit();
            }
        }*/
    }
}
