#if defined(DM_PLATFORM_ANDROID)

#pragma once

#include <dmsdk/sdk.h>

namespace dmUtils {
    void showMailIntent(const char* mailUri);
    void InitializeExtension();
    void showKeyboard();
    void shareText(const char* title, const char* subject, const char* text);
}


#endif