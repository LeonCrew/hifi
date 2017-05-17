//
//  InterfaceActivity.java
//  gvr-interface/java
//
//  Created by Stephen Birarda on 1/26/15.
//  Copyright 2015 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

package io.highfidelity.hifiinterface;

import android.app.Activity;
import android.content.Intent;
import android.content.res.AssetManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.util.Log;
import org.qtproject.qt5.android.bindings.QtActivity;

import com.google.vr.cardboard.DisplaySynchronizer;
import com.google.vr.cardboard.DisplayUtils;
import com.google.vr.ndk.base.GvrApi;
import android.graphics.Point;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class InterfaceActivity extends QtActivity {

    public static native void handleHifiURL(String hifiURLString);
    private native long nativeOnCreate(AssetManager assetManager, long gvrContextPtr);
    private native void saveRealScreenSize(int width, int height);

    private AssetManager assetManager;

    private TextView tv = null;

    // Opaque native pointer to the Application C++ object.
    // This object is owned by the InterfaceActivity instance and passed to the native methods.
    //private long nativeGvrApi;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

//        tv = new TextView(this);
//        tv.setText("TEXT");
//        tv.setLayoutParams(new LinearLayout.LayoutParams(
//                LinearLayout.LayoutParams.FILL_PARENT,
//                LinearLayout.LayoutParams.FILL_PARENT));
//
//        tv.setOnClickListener(new View.OnClickListener() {
//
//            @Override
//            public void onClick(View v) {
//                ((ViewGroup)tv.getParent()).removeView(tv);
//                tv = null;
//            }
//        });
//
//        setContentView(tv);


        // Get the intent that started this activity in case we have a hifi:// URL to parse
        Intent intent = getIntent();
        if (intent.getAction() == Intent.ACTION_VIEW) {
            Uri data = intent.getData();
        
            if (data.getScheme().equals("hifi")) {
                handleHifiURL(data.toString());
            }
        }
        
        DisplaySynchronizer displaySynchronizer = new DisplaySynchronizer(this, DisplayUtils.getDefaultDisplay(this));
        GvrApi gvrApi = new GvrApi(this, displaySynchronizer);
        Log.d("GVR", "gvrApi.toString(): " + gvrApi.toString());

        assetManager = getResources().getAssets();

        //nativeGvrApi =
            nativeOnCreate(assetManager, gvrApi.getNativeGvrContext());

        Point size = new Point();
        getWindowManager().getDefaultDisplay().getRealSize(size);
        saveRealScreenSize(size.x, size.y);

        //Intent intent2 = new Intent(this, SwitchActivity.class);
        //startActivity(intent2);

        final Handler handler = new Handler();
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                Intent intent2 = new Intent(InterfaceActivity.this, SwitchActivity.class);
                startActivity(intent2);
            }
        }, 3000);
    }
}