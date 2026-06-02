/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_TEST_BASE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_TEST_BASE_H_

#include <memory>

#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/actions/conversion_action_types.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/test/conversions_observer_mock.h"

namespace catsxp_ads {

class Conversions;
struct AdInfo;
namespace test {

class CatsxpAdsConversionsTestBase : public TestBase {
 public:
  CatsxpAdsConversionsTestBase(const CatsxpAdsConversionsTestBase&) = delete;
  CatsxpAdsConversionsTestBase& operator=(const CatsxpAdsConversionsTestBase&) =
      delete;

  ~CatsxpAdsConversionsTestBase() override;

  // TestBase:
  void SetUp() override;
  void TearDown() override;

 protected:
  CatsxpAdsConversionsTestBase();

  void VerifyOnDidConvertAdExpectation(
      const AdInfo& ad,
      ConversionActionType action_type,
      base::OnceClosure did_convert_ad_closure);

  void VerifyOnDidNotConvertAdExpectation();


  std::unique_ptr<Conversions> conversions_;

  ConversionsObserverMock conversions_observer_mock_;
};

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_TEST_BASE_H_
