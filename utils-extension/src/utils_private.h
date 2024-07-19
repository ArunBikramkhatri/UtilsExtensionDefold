#if defined(DM_PLATFORM_ANDROID)

#pragma once

#include <dmsdk/sdk.h>

namespace dmUtils {
    void showMailIntent(const char* mailUri);
    void InitializeExtension();
}


#endif