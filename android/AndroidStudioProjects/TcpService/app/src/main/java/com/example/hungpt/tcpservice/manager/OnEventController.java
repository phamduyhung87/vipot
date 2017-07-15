package com.example.hungpt.tcpservice.manager;

import android.view.View;

/**
 * Created by danhdueexoictif on 5/20/17.
 */

public interface OnEventController
{

    interface NETWORK_EVENT
    {
        int NO_CONNECTION = 1;
        int CONNECTION_TIME_OUT = 2;
        int SERVER_ERROR = 3;
        int PARSE_ERROR = 4;
        int LOAD_DATA_FAIL = 5;
    }

    interface ACTIVITY_EVENT
    {
        int MAIN_AC_FINISH = 100001;
        int MAIN_AC_SHOW_MESSAGE = 100002;
    }

    interface SERVICE_EVENT
    {
        int MY_SERVICE_SHOW_MSG_SUCCESS = 200001;
    }

    /**
     * Send data and Handle Event in App
     * @param eventType
     * @param view
     * @param data
     */
    void onEvent(int eventType, View view, Object data);
}