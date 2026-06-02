/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_rewards/user_rewards_util.h"

#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/test/issuers_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_client/test/ads_client_notifier_observer_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_notifier_observer.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds

namespace catsxp_ads {

class CatsxpAdsUserRewardsUtilTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    observation_.Observe(&GetAdsClient());
  }

  AdsClientNotifierObserverMock ads_client_notifier_observer_mock_;
  base::ScopedObservation<AdsClient, AdsClientNotifierObserver> observation_{
      &ads_client_notifier_observer_mock_};
};

TEST_F(CatsxpAdsUserRewardsUtilTest, UpdateIssuers) {
  // Arrange
  EXPECT_CALL(ads_client_notifier_observer_mock_,
              OnNotifyPrefDidChange(prefs::kIssuerPing));
  EXPECT_CALL(ads_client_notifier_observer_mock_,
              OnNotifyPrefDidChange(prefs::kIssuers));

  const IssuersInfo issuers = test::BuildIssuers();

  // Act
  UpdateIssuers(issuers);

  // Assert
  EXPECT_TRUE(HasIssuers());
}

TEST_F(CatsxpAdsUserRewardsUtilTest, DoNotUpdateIfIssuersHasNotChanged) {
  // Arrange
  test::BuildAndSetIssuers();

  EXPECT_CALL(ads_client_notifier_observer_mock_,
              OnNotifyPrefDidChange(prefs::kIssuerPing))
      .Times(0);
  EXPECT_CALL(ads_client_notifier_observer_mock_,
              OnNotifyPrefDidChange(prefs::kIssuers))
      .Times(0);

  const IssuersInfo issuers = test::BuildIssuers();

  // Act
  UpdateIssuers(issuers);

  // Assert
  EXPECT_TRUE(HasIssuers());
}

}  // namespace catsxp_ads
