/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_types.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_util.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsNonAnonymousUrlHostTest : public test::TestBase {};

TEST_F(CatsxpAdsNonAnonymousUrlHostTest, GetProductionUrlHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->CommandLineSwitches().environment_type =
      mojom::EnvironmentType::kProduction;

  // Act & Assert
  EXPECT_EQ("https://mywallet.ads.catsxp.com",
            GetUrlHost(UrlHostType::kNonAnonymous));
}

TEST_F(CatsxpAdsNonAnonymousUrlHostTest, GetStagingUrlHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->CommandLineSwitches().environment_type =
      mojom::EnvironmentType::kStaging;

  // Act & Assert
  EXPECT_EQ("https://mywallet.ads.catsxpsoftware.com",
            GetUrlHost(UrlHostType::kNonAnonymous));
}

}  // namespace catsxp_ads
