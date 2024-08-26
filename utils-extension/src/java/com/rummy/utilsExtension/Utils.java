package com.rummy.utilsExtension;

import com.rummy.utilsExtension.URI.URIOperations;

import android.app.Activity;
import android.util.Log;

class Utils {

    private static final String TAG = "Utils";
    private Activity activity;
    private URIOperations uriOp;
    private KeyboardUtils KeyboardUtils;

    public Utils(Activity activity) {
        this.activity = activity;
        uriOp = new URIOperations(activity);
        KeyboardUtils = new KeyboardUtils(activity);
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

    public void showKeyboard() {
        try {
            System.out.println("showkeyboard");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void shareText(String title, String subject, String text) {
        try {
            uriOp.shareText(title, subject, text);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}