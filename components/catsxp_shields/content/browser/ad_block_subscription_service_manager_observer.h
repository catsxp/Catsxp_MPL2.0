/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_SERVICE_MANAGER_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_SERVICE_MANAGER_OBSERVER_H_

#include "base/observer_list_types.h"

namespace catsxp_shields {

class AdBlockSubscriptionServiceManagerObserver : public base::CheckedObserver {
 public:
  ~AdBlockSubscriptionServiceManagerObserver() override = default;
  virtual void OnServiceUpdateEvent() {}
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_SERVICE_MANAGER_OBSERVER_H_
