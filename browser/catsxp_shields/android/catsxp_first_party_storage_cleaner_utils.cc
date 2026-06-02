/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include <cstddef>

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "catsxp/browser/catsxp_shields/android/jni_headers/CatsxpFirstPartyStorageCleanerUtils_jni.h"
#include "catsxp/browser/catsxp_shields/catsxp_shields_tab_helper.h"
#include "catsxp/browser/ephemeral_storage/ephemeral_storage_service_factory.h"
#include "catsxp/browser/ephemeral_storage/ephemeral_storage_tab_helper.h"
#include "chrome/browser/android/tab_android.h"
#include "chrome/browser/profiles/profile.h"

namespace catsxp_shields {

static void JNI_CatsxpFirstPartyStorageCleanerUtils_CleanupTLDFirstPartyStorage(
    JNIEnv* env,
    const jni_zero::JavaRef<jobject>& tab_object) {
  CHECK(env);
  // Validate that GetNativeTab returned a valid TabAndroid pointer
  // GetNativeTab handles null JavaRef validation internally
  TabAndroid* tab_android = TabAndroid::GetNativeTab(env, tab_object);
  if (!tab_android) {
    return;
  }

  content::WebContents* web_contents = tab_android->web_contents();
  if (!web_contents) {
    return;
  }

  catsxp_shields::CatsxpShieldsTabHelper* catsxp_shields_tab_helper =
      catsxp_shields::CatsxpShieldsTabHelper::GetOrCreateForWebContents(
          web_contents);
  if (!catsxp_shields_tab_helper) {
    return;
  }

  catsxp_shields_tab_helper->EnforceSiteDataCleanup();
}

static void
JNI_CatsxpFirstPartyStorageCleanerUtils_TriggerCurrentAppStateNotification(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile) {
  CHECK(env);
  Profile* profile = Profile::FromJavaObject(j_profile);
  if (!profile) {
    return;
  }

  auto* ephemeral_storage_service =
      EphemeralStorageServiceFactory::GetForContext(
          static_cast<content::BrowserContext*>(profile));
  if (!ephemeral_storage_service) {
    return;
  }

  ephemeral_storage_service->TriggerCurrentAppStateNotification();
}

}  // namespace catsxp_shields

DEFINE_JNI(CatsxpFirstPartyStorageCleanerUtils)
