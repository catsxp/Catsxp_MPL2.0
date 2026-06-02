/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/playlist/playlist_service_factory.h"

#include "base/android/jni_android.h"
#include "chrome/android/chrome_jni_headers/PlaylistServiceFactoryAndroid_jni.h"
#include "chrome/browser/profiles/profile.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"

namespace chrome {
namespace android {
static jlong JNI_PlaylistServiceFactoryAndroid_GetInterfaceToPlaylistService(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& profile_android) {
  auto* profile = Profile::FromJavaObject(profile_android);
  auto pending =
      playlist::PlaylistServiceFactory::GetInstance()->GetRemoteForProfile(
          profile);

  return static_cast<jlong>(pending.PassPipe().release().value());
}

}  // namespace android
}  // namespace chrome

DEFINE_JNI(PlaylistServiceFactoryAndroid)
