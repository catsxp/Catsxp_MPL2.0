/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_types.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsUrlHostUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsUrlHostUtilTest, GetUrlHostReturnsStaticHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->CommandLineSwitches().environment_type =
      mojom::EnvironmentType::kProduction;

  // Act & Assert
  EXPECT_EQ("https://static.ads.catsxp.com", GetUrlHost(UrlHostType::kStatic));
}

TEST_F(CatsxpAdsUrlHostUtilTest, GetUrlHostReturnsGeoHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->CommandLineSwitches().environment_type =
      mojom::EnvironmentType::kProduction;

  // Act & Assert
  EXPECT_EQ("https://geo.ads.catsxp.com", GetUrlHost(UrlHostType::kGeo));
}

TEST_F(CatsxpAdsUrlHostUtilTest, GetUrlHostReturnsNonAnonymousHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->CommandLineSwitches().environment_type =
      mojom::EnvironmentType::kProduction;

  // Act & Assert
  EXPECT_EQ("https://mywallet.ads.catsxp.com",
            GetUrlHost(UrlHostType::kNonAnonymous));
}

TEST_F(CatsxpAdsUrlHostUtilTest, GetUrlHostReturnsAnonymousHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->CommandLineSwitches().environment_type =
      mojom::EnvironmentType::kProduction;

  // Act & Assert
  EXPECT_EQ("https://anonymous.ads.catsxp.com",
            GetUrlHost(UrlHostType::kAnonymous));
}

TEST_F(CatsxpAdsUrlHostUtilTest, GetUrlHostReturnsAnonymousSearchHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->CommandLineSwitches().environment_type =
      mojom::EnvironmentType::kProduction;

  // Act & Assert
  EXPECT_EQ("https://search.anonymous.ads.catsxp.com",
            GetUrlHost(UrlHostType::kAnonymousSearch));
}

}  // namespace catsxp_ads
