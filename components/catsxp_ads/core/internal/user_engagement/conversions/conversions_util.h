/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_UTIL_H_

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

struct AdEventInfo;

bool IsAllowedToConvertAdEvent(const AdEventInfo& ad_event);

bool DidAdEventOccurWithinObservationWindow(const AdEventInfo& ad_event,
                                            base::TimeDelta observation_window);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_UTIL_H_
