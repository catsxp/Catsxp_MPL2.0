/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/device_id/device_id_impl.h"

#include <utility>

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "base/functional/callback.h"
#include "catsxp/browser/catsxp_ads/android/jni_headers/DeviceIdImplAndroid_jni.h"

namespace catsxp_ads {

// static
void DeviceIdImpl::GetRawDeviceId(DeviceIdCallback callback) {
  JNIEnv* env = base::android::AttachCurrentThread();
  base::android::ScopedJavaLocalRef<jstring> android_id =
      Java_DeviceIdImplAndroid_getAndroidId(env);
  if (!android_id) {
    return std::move(callback).Run({});
  }

  std::string device_id =
      base::android::ConvertJavaStringToUTF8(env, android_id.obj());
  std::move(callback).Run(std::move(device_id));
}

}  // namespace catsxp_ads
