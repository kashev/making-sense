package com.example.making_sense;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

public class HandTemp extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hand_temp);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.hand_temp, menu);
        return true;
    }
    
}
