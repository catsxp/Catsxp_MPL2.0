/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_ACTIONS_CONVERSION_ACTION_TYPES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_ACTIONS_CONVERSION_ACTION_TYPES_H_

namespace catsxp_ads {

enum class ConversionActionType {
  kUndefined = 0,

  // View-through conversions occur when a user is exposed to an ad viewed
  // impression and later completes a desired action, such as making a purchase
  // or filling out a form. The conversion is attributed to the ad view
  // impression rather than a direct click.
  kViewThrough,

  // Click-through conversions occur when a user clicks on an ad and later
  // completes a desired action, such as making a purchase or filling out a
  // form. Click-through conversions should take priority over view-through.
  kClickThrough
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_ACTIONS_CONVERSION_ACTION_TYPES_H_
