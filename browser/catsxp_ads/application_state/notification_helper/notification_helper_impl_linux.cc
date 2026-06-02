/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/application_state/notification_helper/notification_helper_impl_linux.h"

#include "base/feature_list.h"
#include "base/logging.h"
#include "chrome/common/chrome_features.h"

namespace catsxp_ads {

NotificationHelperImplLinux::NotificationHelperImplLinux() = default;

NotificationHelperImplLinux::~NotificationHelperImplLinux() = default;

bool NotificationHelperImplLinux::CanShowNotifications() {
  // TODO(https://github.com/catsxp/catsxp-browser/issues/5542): Investigate how
  // to detect if notifications are enabled within the Linux operating system

  if (!base::FeatureList::IsEnabled(::features::kNativeNotifications)) {
    LOG(WARNING) << "Native notifications feature is disabled";
    return false;
  }

  return true;
}

bool NotificationHelperImplLinux::
    CanShowSystemNotificationsWhileBrowserIsBackgrounded() const {
  return true;
}

bool NotificationHelperImplLinux::ShowOnboardingNotification() {
  return false;
}

}  // namespace catsxp_ads
