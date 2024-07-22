package com.rummy.utilsExtension;

import android.app.Activity;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.ViewGroup;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.TextView;

public class KeyboardUtils {
    private static final String TAG = "KeyboardUtils";
    private Activity activity;

    private EditText editText;

    public KeyboardUtils(Activity activity) {
        Log.d(TAG, "keyboard constructor called");
        this.activity = activity;

    }

    public void showKeyboard() {
        if (activity == null) {
            Log.d(TAG, "activity is null.");
            return;
        }

        editText = new EditText(activity);

        editText.setImeOptions(EditorInfo.IME_ACTION_DONE);
        editText.setLayoutParams(
                new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
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

        editText.setText("");
        try {
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (editText.getParent() == null) {
                        // Add the EditText to a view that overlays everything
                        ViewGroup rootView = (ViewGroup) activity.findViewById(android.R.id.content);
                        rootView.addView(editText, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                                ViewGroup.LayoutParams.MATCH_PARENT));
                    }
                    editText.setVisibility(View.VISIBLE);
                    editText.setSingleLine(true);
                    editText.bringToFront();
                    editText.requestFocus();
                    InputMethodManager imm = (InputMethodManager) activity
                            .getSystemService(Activity.INPUT_METHOD_SERVICE);
                    if (imm != null) {
                        imm.showSoftInput(editText, InputMethodManager.SHOW_IMPLICIT);
                        Log.d(TAG, "showKeyboard: ");
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
        Log.d(TAG, "removeTextEdit: ");
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
