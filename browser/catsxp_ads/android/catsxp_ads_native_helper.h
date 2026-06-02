/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_ANDROID_CATSXP_ADS_NATIVE_HELPER_H_
#define CATSXP_BROWSER_CATSXP_ADS_ANDROID_CATSXP_ADS_NATIVE_HELPER_H_

#include "base/android/scoped_java_ref.h"

namespace catsxp_ads {

static jboolean JNI_CatsxpAdsNativeHelper_IsOptedInToNotificationAds(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android);

static void JNI_CatsxpAdsNativeHelper_SetOptedInToNotificationAds(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android,
    jboolean opted_in);

static jboolean JNI_CatsxpAdsNativeHelper_IsSupportedRegion(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android);

static void JNI_CatsxpAdsNativeHelper_ClearData(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android);

static void JNI_CatsxpAdsNativeHelper_OnNotificationAdShown(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android,
    const base::android::JavaRef<jstring>& j_notification_id);

static void JNI_CatsxpAdsNativeHelper_OnNotificationAdClosed(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android,
    const base::android::JavaRef<jstring>& j_notification_id,
    jboolean j_by_user);

static void JNI_CatsxpAdsNativeHelper_OnNotificationAdClicked(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& j_profile_android,
    const base::android::JavaRef<jstring>& j_notification_id);

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_ANDROID_CATSXP_ADS_NATIVE_HELPER_H_
