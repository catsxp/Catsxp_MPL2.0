/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/test/ad_event_test_util.h"

#include "base/check_op.h"
#include "base/functional/bind.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace catsxp_ads::test {

namespace {

void RecordAdEvent(const AdEventInfo& ad_event) {
  RecordAdEvent(ad_event,
                base::BindOnce([](bool success) { ASSERT_TRUE(success); }));
}

}  // namespace

void RecordAdEvent(const AdInfo& ad,
                   mojom::ConfirmationType mojom_confirmation_type) {
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom_confirmation_type, /*created_at=*/Now());
  RecordAdEvent(ad_event);
}

void RecordAdEvents(
    const AdInfo& ad,
    const std::vector<mojom::ConfirmationType>& mojom_confirmation_types) {
  for (const auto& mojom_confirmation_type : mojom_confirmation_types) {
    RecordAdEvent(ad, mojom_confirmation_type);
  }
}

void RecordAdEvents(const AdInfo& ad,
                    mojom::ConfirmationType mojom_confirmation_type,
                    size_t count) {
  CHECK_GT(count, 0U);

  for (size_t i = 0; i < count; ++i) {
    RecordAdEvent(ad, mojom_confirmation_type);
  }
}

}  // namespace catsxp_ads::test
