/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_INTERFACE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_INTERFACE_H_

#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads {

template <typename T>
class AdEventInterface {
 public:
  virtual ~AdEventInterface() = default;

  // Invoked to fire an ad event.
  virtual void FireEvent(const T&, ResultCallback callback) = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_INTERFACE_H_
