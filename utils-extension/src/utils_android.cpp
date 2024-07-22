#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/dlib/android.h>
#include "utils_private.h"


namespace dmUtils {

    struct Utils 
    {
        jobject m_UtilsJNI;
        jmethodID m_startMailIntent;
        jmethodID m_showKeyboard;

    };

    static Utils g_uitls ;


    static void InitJNIMethods(JNIEnv* env , jclass cls){
        g_uitls.m_startMailIntent= env->GetMethodID(cls , "openURI" ,"(Ljava/lang/String;)V");
        g_uitls.m_showKeyboard = env->GetMethodID(cls , "showKeyboard" ,"()V;");
    }

    void InitializeExtension(){

        dmAndroid::ThreadAttacher threadAttacher;

        JNIEnv* env = threadAttacher.GetEnv();

        jclass cls = dmAndroid::LoadClass(env , "com.rummy.utilsExtension.Utils");
        InitJNIMethods(env ,cls);
        jmethodID jni_constructor = env->GetMethodID(cls , "<init>" ,"(Landroid/app/Activity;)V");
        if (jni_constructor == nullptr) {
            dmLogInfo("Failed to get constructor ID for URIOperations");
            return;
        }

        jobject native_activity = dmGraphics::GetNativeAndroidActivity();
        jobject localRef = env->NewObject(cls, jni_constructor, native_activity);
        if (localRef == nullptr) {
            dmLogInfo("Failed to create new URIOperations object");
            return;
        }

        g_uitls.m_UtilsJNI = env->NewGlobalRef(localRef);
        env->DeleteLocalRef(localRef);

        if (g_uitls.m_UtilsJNI == nullptr) {
            dmLogInfo("Failed to create global reference for URIOperations object");
        }
    }


    static void CallVoidMethod(jobject instance , jmethodID method){
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();
        env->CallVoidMethod(instance, method);
    }

    

    static void CallVoidMethodChar(jobject instance , jmethodID method, const char* cstr){
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();
        jstring jstr = env->NewStringUTF(cstr);
        env->CallVoidMethod(instance, method ,jstr);
        env->DeleteLocalRef(jstr);
    }
    void showMailIntent(const char* mailUri){
        CallVoidMethodChar(g_uitls.m_UtilsJNI , g_uitls.m_startMailIntent ,mailUri);
    }

    void showKeyboard)(){
        CallVoidMethod(g_uitls.m_UtilsJNI , g_uitls.m_showKeyboard);
    }

}

#endif
