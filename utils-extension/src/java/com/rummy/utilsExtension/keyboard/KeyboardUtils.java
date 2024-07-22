package com.rummy.utilsExtension;

import android.app.Activity;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.ViewGroup;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.TextView;

public class KeyboardUtils {
    private static final String TAG = "KeyboardUtils";
    private Activity activity;

    private EditText editText;

    public KeyboardUtils(Activity activity) {
        this.activity = activity;
        editText = new EditText(activity);
        editText.setSingleLine(true);
        editText.bringToFront();
        editText.setImeOptions(EditorInfo.IME_ACTION_DONE);
        editText.setLayoutParams(new ViewGroup.LayoutParams(0, 0));
        editText.setGravity(Gravity.TOP);
        editText.setImeOptions(EditorInfo.IME_FLAG_NO_FULLSCREEN);

        editText.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                if (actionId == EditorInfo.IME_ACTION_DONE) {
                    removeTextEdit();
                    return true;
                }
                return false;
            }
        });
    }

    public void showKeyboard() {
        editText.setText("");
        try {
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (editText.getParent() == null) {
                        activity.addContentView(editText, new ViewGroup.LayoutParams(
                                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
                    }
                    editText.requestFocus();
                    InputMethodManager imm = (InputMethodManager) activity
                            .getSystemService(Activity.INPUT_METHOD_SERVICE);
                    if (imm != null) {
                        imm.showSoftInput(editText, InputMethodManager.SHOW_IMPLICIT);
                    }

                }
            });
        } catch (Exception e) {
            Log.e(TAG, "showKeyboard: " + e.getLocalizedMessage(), e);
            e.printStackTrace();
        }
    }

    public void hideKeyboard() {
        try {
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    InputMethodManager imm = (InputMethodManager) activity
                            .getSystemService(Activity.INPUT_METHOD_SERVICE);
                    if (imm != null) {
                        imm.hideSoftInputFromWindow(editText.getWindowToken(), 0);
                    }
                    removeTextEdit();
                }
            });
        } catch (Exception e) {
            Log.e(TAG, "hideKeyboard: " + e.getLocalizedMessage(), e);
            e.printStackTrace();
        }
    }

    private void removeTextEdit() {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ViewGroup parent = (ViewGroup) editText.getParent();
                if (parent != null) {
                    parent.removeView(editText);
                }
            }
        });
    }
}
