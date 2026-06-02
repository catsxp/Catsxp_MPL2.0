/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NOTIFICATION_AD_TEST_NOTIFICATION_AD_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NOTIFICATION_AD_TEST_NOTIFICATION_AD_TEST_UTIL_H_

namespace catsxp_ads {

struct NotificationAdInfo;

namespace test {

NotificationAdInfo BuildNotificationAd(bool use_random_uuids);

NotificationAdInfo BuildAndSaveNotificationAd(bool use_random_uuids);

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NOTIFICATION_AD_TEST_NOTIFICATION_AD_TEST_UTIL_H_
