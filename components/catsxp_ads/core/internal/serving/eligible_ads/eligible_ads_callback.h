/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ELIGIBLE_ADS_CALLBACK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ELIGIBLE_ADS_CALLBACK_H_

#include "base/functional/callback.h"

namespace catsxp_ads {

template <typename T>
using EligibleAdsCallback = base::OnceCallback<void(T eligible_ads)>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ELIGIBLE_ADS_CALLBACK_H_
