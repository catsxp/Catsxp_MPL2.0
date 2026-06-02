/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_VALUE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_VALUE_UTIL_H_

#include "base/containers/circular_deque.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

struct NotificationAdInfo;

base::DictValue NotificationAdToDict(const NotificationAdInfo& ad);
base::ListValue NotificationAdsToList(
    const base::circular_deque<NotificationAdInfo>& ads);

NotificationAdInfo NotificationAdFromDict(const base::DictValue& dict);
base::circular_deque<NotificationAdInfo> NotificationAdsFromList(
    const base::ListValue& list);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_VALUE_UTIL_H_
