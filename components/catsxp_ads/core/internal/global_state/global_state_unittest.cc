/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsGlobalStateTest : public test::TestBase {};

TEST_F(CatsxpAdsGlobalStateTest, HasInstance) {
  // Act & Assert
  EXPECT_TRUE(GlobalState::HasInstance());
}

}  // namespace catsxp_ads
