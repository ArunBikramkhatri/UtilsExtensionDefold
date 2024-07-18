package com.rummy.utilsExtension;

import com.rummy.utilsExtension.URI.URIOperations;

import android.app.Activity;
import android.util.Log;

class Utils {

    private static final String TAG = "Utils";
    private Activity activity;
    private URIOperations uriOp;

    public Utils(Activity activity) {
        this.activity = activity;
        uriOp = new URIOperations(activity);
    }

    public void openURI(String uri) {
        try {
            if (uri != null) {
                uriOp.openURI(uri);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}