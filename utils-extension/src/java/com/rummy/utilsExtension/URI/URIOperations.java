
package com.rummy.utilsExtension.URI;

import android.app.Activity;
import android.util.Log;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.net.Uri;
import androidx.core.content.FileProvider;

import java.io.File;

public class URIOperations {

    private static final String TAG = "MailURI";
    private Activity activity;

    public URIOperations(Activity activity) {
        this.activity = activity;
    }

    public void openURI(String uriString) {
        try {
            Uri dataUri;
            String dataType = "";
            boolean grantReadUriPermission = false;

            if (uriString.startsWith("/") || uriString.startsWith("file://")) {
                String filePath = uriString;
                // File uris needs to be provided via the FileProvider
                grantReadUriPermission = true;
                if (filePath.startsWith("file://")) {
                    filePath = filePath.replace("file://", "");
                }

                File targetFile = new File(filePath);
                dataUri = FileProvider.getUriForFile(activity, activity.getPackageName() + ".fileprovider", targetFile);
                dataType = activity.getContentResolver().getType(dataUri);
            } else {
                dataUri = Uri.parse(uriString);
            }

            Intent intent = new Intent();
            intent.setAction(Intent.ACTION_VIEW);
            if (TextUtils.isEmpty(dataType)) {
                intent.setData(dataUri);
            } else {
                intent.setDataAndType(dataUri, dataType);
            }
            if (grantReadUriPermission) {
                intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
            }

            activity.startActivity(intent);
        } catch (Exception e) {
            Log.e(TAG, "Unable to open uri " + uriString, e);
          
        }
    }
}
