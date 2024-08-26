#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/dlib/android.h>
#include "utils_private.h"


namespace dmUtils {

    struct Utils 
    {
        jobject m_UtilsJNI;
        jmethodID m_startMailIntent;
        jmethodID m_showKeyboard;
        jmethodID m_shareText;

    };

    static Utils g_utils ;


    static void InitJNIMethods(JNIEnv* env, jclass cls) {
        g_utils.m_startMailIntent = env->GetMethodID(cls, "openURI", "(Ljava/lang/String;)V");
        g_utils.m_showKeyboard = env->GetMethodID(cls, "showKeyboard", "()V");
       g_utils.m_shareText = env->GetMethodID(cls, "shareText", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
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

        // jobject native_activity = dmGraphics::GetNativeAndroidActivity();
        jobject native_activity = threadAttacher.GetActivity()->clazz;
        jobject localRef = env->NewObject(cls, jni_constructor, native_activity);
        if (localRef == nullptr) {
            dmLogInfo("Failed to create new URIOperations object");
            return;
        }

        g_utils.m_UtilsJNI = env->NewGlobalRef(localRef);
        env->DeleteLocalRef(localRef);

        if (g_utils.m_UtilsJNI == nullptr) {
            dmLogInfo("Failed to create global reference for URIOperations object");
        }
    }


    static void CallVoidMethod(jobject instance , jmethodID method){
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();
        env->CallVoidMethod(instance, method);
    }

    static void CallVoidMethodCharCharChar(jobject instance , jmethodID method,const char* cstr ,const char* cstr1,const char* cstr2){
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();
        jstring jstr = env->NewStringUTF(cstr);
        jstring jstr1 = env->NewStringUTF(cstr1);
        jstring jstr2 = env->NewStringUTF(cstr2);
        env->CallVoidMethod(instance, method ,jstr , jstr1, jstr2);
        env->DeleteLocalRef(jstr);
        env->DeleteLocalRef(jstr1);
        env->DeleteLocalRef(jstr2);
    }

    static void CallVoidMethodChar(jobject instance , jmethodID method, const char* cstr){
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();
        jstring jstr = env->NewStringUTF(cstr);
        env->CallVoidMethod(instance, method ,jstr);
        env->DeleteLocalRef(jstr);
    }

    void showMailIntent(const char* mailUri){
        CallVoidMethodChar(g_utils.m_UtilsJNI , g_utils.m_startMailIntent ,mailUri);
    }

    void showKeyboard(){
        CallVoidMethod(g_utils.m_UtilsJNI , g_utils.m_showKeyboard);
    }

    void shareText(const char* title, const char* subject, const char* text){
        CallVoidMethodCharCharChar(g_utils.m_UtilsJNI , g_utils.m_shareText , title , subject , text);
    }
}

#endif
