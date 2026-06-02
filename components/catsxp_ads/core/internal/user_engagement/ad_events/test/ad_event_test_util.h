/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_TEST_AD_EVENT_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_TEST_AD_EVENT_TEST_UTIL_H_

#include <cstddef>
#include <vector>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct AdInfo;

namespace test {

void RecordAdEvent(const AdInfo& ad,
                   mojom::ConfirmationType mojom_confirmation_type);

void RecordAdEvents(
    const AdInfo& ad,
    const std::vector<mojom::ConfirmationType>& mojom_confirmation_types);

void RecordAdEvents(const AdInfo& ad,
                    mojom::ConfirmationType mojom_confirmation_type,
                    size_t count);

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_TEST_AD_EVENT_TEST_UTIL_H_
