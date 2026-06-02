/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/application_state/notification_helper/notification_helper_impl.h"

namespace catsxp_ads {

NotificationHelperImpl::NotificationHelperImpl() = default;

NotificationHelperImpl::~NotificationHelperImpl() = default;

void NotificationHelperImpl::InitSystemNotifications() {}

bool NotificationHelperImpl::CanShowNotifications() {
  return true;
}

bool NotificationHelperImpl::
    CanShowSystemNotificationsWhileBrowserIsBackgrounded() const {
  return true;
}

bool NotificationHelperImpl::ShowOnboardingNotification() {
  return false;
}

}  // namespace catsxp_ads
