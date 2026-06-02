/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_HANDLER_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_HANDLER_UTIL_H_

namespace catsxp_ads {

bool ShouldServe();

bool CanServeIfUserIsActive();

bool CanServeAtRegularIntervals();
bool ShouldServeAtRegularIntervals();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_HANDLER_UTIL_H_
