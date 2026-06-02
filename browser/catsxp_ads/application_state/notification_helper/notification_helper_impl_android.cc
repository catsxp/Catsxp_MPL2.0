/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/application_state/notification_helper/notification_helper_impl_android.h"

#include "base/android/jni_string.h"
#include "base/system/sys_info.h"
#include "catsxp/browser/catsxp_ads/android/jni_headers/CatsxpAdsSignupDialog_jni.h"
#include "catsxp/browser/catsxp_ads/android/jni_headers/CatsxpAds_jni.h"
#include "catsxp/build/android/jni_headers/CatsxpSiteChannelsManagerBridge_jni.h"
#include "catsxp/components/catsxp_ads/browser/application_state/application_state_monitor.h"
#include "chrome/browser/notifications/jni_headers/NotificationSystemStatusUtil_jni.h"
#include "chrome/browser/notifications/notification_channels_provider_android.h"

namespace catsxp_ads {

namespace {

constexpr int kMinimumMajorOperatingSystemVersionForNotificationChannels = 8;

constexpr int kAppNotificationStatusUndeterminable = 0;
constexpr int kAppNotificationsStatusEnabled = 2;

int GetOperatingSystemMajorVersion() {
  int32_t major_version = 0;
  int32_t minor_version = 0;
  int32_t bugfix_version = 0;

  base::SysInfo::OperatingSystemVersionNumbers(&major_version, &minor_version,
                                               &bugfix_version);

  return major_version;
}

bool IsCatsxpAdsNotificationChannelEnabled(bool is_foreground) {
  if (GetOperatingSystemMajorVersion() <
      kMinimumMajorOperatingSystemVersionForNotificationChannels) {
    return true;
  }

  JNIEnv* env = jni_zero::AttachCurrentThread();

  const auto j_channel_id =
      (is_foreground) ? Java_CatsxpAds_getCatsxpAdsChannelId(env)
                      : Java_CatsxpAds_getCatsxpAdsBackgroundChannelId(env);

  const auto status = static_cast<NotificationChannelStatus>(
      Java_CatsxpSiteChannelsManagerBridge_getChannelStatus(env, j_channel_id));

  return (status == NotificationChannelStatus::ENABLED ||
          status == NotificationChannelStatus::UNAVAILABLE);
}

}  // namespace

NotificationHelperImplAndroid::NotificationHelperImplAndroid() = default;

NotificationHelperImplAndroid::~NotificationHelperImplAndroid() = default;

bool NotificationHelperImplAndroid::CanShowNotifications() {
  JNIEnv* env = jni_zero::AttachCurrentThread();
  const int status =
      Java_NotificationSystemStatusUtil_getAppNotificationStatus(env);

  const bool is_notifications_enabled =
      (status == kAppNotificationsStatusEnabled ||
       status == kAppNotificationStatusUndeterminable);

  const bool is_foreground =
      ApplicationStateMonitor::GetInstance()->IsBrowserActive();

  const bool is_notification_channel_enabled =
      IsCatsxpAdsNotificationChannelEnabled(is_foreground);

  bool can_show_native_notifications =
      is_notifications_enabled && is_notification_channel_enabled;

  if (!is_foreground) {
    can_show_native_notifications =
        can_show_native_notifications &&
        CanShowSystemNotificationsWhileBrowserIsBackgrounded();
  }

  return can_show_native_notifications;
}

bool NotificationHelperImplAndroid::
    CanShowSystemNotificationsWhileBrowserIsBackgrounded() const {
  JNIEnv* env = jni_zero::AttachCurrentThread();
  return Java_CatsxpAdsSignupDialog_showAdsInBackground(env);
}

bool NotificationHelperImplAndroid::ShowOnboardingNotification() {
  JNIEnv* env = jni_zero::AttachCurrentThread();
  Java_CatsxpAdsSignupDialog_enqueueOnboardingNotificationNative(env);

  return true;
}

}  // namespace catsxp_ads
