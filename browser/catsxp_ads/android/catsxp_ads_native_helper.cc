/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/android/catsxp_ads_native_helper.h"

#include <string>

#include "base/android/jni_string.h"
#include "base/functional/callback_helpers.h"
#include "catsxp/browser/catsxp_ads/ads_service_factory.h"
#include "catsxp/browser/catsxp_ads/android/jni_headers/CatsxpAdsNativeHelper_jni.h"
#include "catsxp/components/catsxp_ads/core/browser/service/ads_service.h"
#include "catsxp/components/catsxp_ads/core/public/ads_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"

namespace catsxp_ads {

// static
jboolean JNI_CatsxpAdsNativeHelper_IsOptedInToNotificationAds(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  return profile->GetPrefs()->GetBoolean(
      catsxp_ads::prefs::kOptedInToNotificationAds);
}

// static
void JNI_CatsxpAdsNativeHelper_SetOptedInToNotificationAds(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android,
    jboolean should_enable_ads) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  profile->GetPrefs()->SetBoolean(catsxp_ads::prefs::kOptedInToNotificationAds,
                                  should_enable_ads);
}

// static
jboolean JNI_CatsxpAdsNativeHelper_IsSupportedRegion(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  AdsService* ads_service = AdsServiceFactory::GetForProfile(profile);
  if (!ads_service) {
    return false;
  }

  return catsxp_ads::IsSupportedRegion();
}

// static
void JNI_CatsxpAdsNativeHelper_ClearData(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  AdsService* ads_service = AdsServiceFactory::GetForProfile(profile);
  if (!ads_service) {
    return;
  }

  ads_service->ClearData(/*intentional*/ base::DoNothing());
}

// static
void JNI_CatsxpAdsNativeHelper_OnNotificationAdShown(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android,
    const base::android::JavaRef<jstring>& j_notification_id) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  AdsService* ads_service = AdsServiceFactory::GetForProfile(profile);
  if (!ads_service) {
    return;
  }

  const std::string notification_id =
      base::android::ConvertJavaStringToUTF8(env, j_notification_id);
  ads_service->OnNotificationAdShown(notification_id);
}

// static
void JNI_CatsxpAdsNativeHelper_OnNotificationAdClosed(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android,
    const base::android::JavaRef<jstring>& j_notification_id,
    jboolean j_by_user) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  AdsService* ads_service = AdsServiceFactory::GetForProfile(profile);
  if (!ads_service) {
    return;
  }

  const std::string notification_id =
      base::android::ConvertJavaStringToUTF8(env, j_notification_id);
  ads_service->OnNotificationAdClosed(notification_id, j_by_user);
}

// static
void JNI_CatsxpAdsNativeHelper_OnNotificationAdClicked(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android,
    const base::android::JavaRef<jstring>& j_notification_id) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  AdsService* ads_service = AdsServiceFactory::GetForProfile(profile);
  if (!ads_service) {
    return;
  }

  const std::string notification_id =
      base::android::ConvertJavaStringToUTF8(env, j_notification_id);
  ads_service->OnNotificationAdClicked(notification_id);
}

}  // namespace catsxp_ads

DEFINE_JNI(CatsxpAdsNativeHelper)
