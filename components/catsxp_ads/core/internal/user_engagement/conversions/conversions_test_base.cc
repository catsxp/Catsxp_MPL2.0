/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions_test_base.h"

#include <utility>

#include "base/test/gmock_callback_support.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/test/ad_event_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversion/conversion_info.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"

namespace catsxp_ads::test {

CatsxpAdsConversionsTestBase::CatsxpAdsConversionsTestBase() = default;

CatsxpAdsConversionsTestBase::~CatsxpAdsConversionsTestBase() = default;

void CatsxpAdsConversionsTestBase::SetUp() {
  TestBase::SetUp();

  conversions_ = std::make_unique<Conversions>();
  conversions_->AddObserver(&conversions_observer_mock_);
}

void CatsxpAdsConversionsTestBase::TearDown() {
  conversions_->RemoveObserver(&conversions_observer_mock_);

  TestBase::TearDown();
}

void CatsxpAdsConversionsTestBase::VerifyOnDidConvertAdExpectation(
    const AdInfo& ad,
    ConversionActionType action_type,
    base::OnceClosure did_convert_ad_closure) {
  EXPECT_CALL(conversions_observer_mock_,
              OnDidConvertAd(/*conversion=*/::testing::FieldsAre(
                  ad.type, ad.creative_instance_id, ad.creative_set_id,
                  ad.campaign_id, ad.advertiser_id, ad.segment, action_type)))
      .WillOnce(base::test::RunOnceClosure(std::move(did_convert_ad_closure)));
}

void CatsxpAdsConversionsTestBase::VerifyOnDidNotConvertAdExpectation() {
  EXPECT_CALL(conversions_observer_mock_, OnDidConvertAd).Times(0);
}

}  // namespace catsxp_ads::test
