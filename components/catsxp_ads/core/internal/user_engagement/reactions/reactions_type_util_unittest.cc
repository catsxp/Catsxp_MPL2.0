/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/reactions/reactions_type_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsReactionsTypeUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsReactionsTypeUtilTest,
       ToggleLikedReactionTypeFromNeutralToLiked) {
  // Act & Assert
  EXPECT_EQ(mojom::ReactionType::kLiked,
            ToggleLikedReactionType(mojom::ReactionType::kNeutral));
}

TEST_F(CatsxpAdsReactionsTypeUtilTest,
       ToggleLikedReactionTypeFromLikedToNeutral) {
  // Act & Assert
  EXPECT_EQ(mojom::ReactionType::kNeutral,
            ToggleLikedReactionType(mojom::ReactionType::kLiked));
}

TEST_F(CatsxpAdsReactionsTypeUtilTest,
       ToggleLikedReactionTypeFromDislikedToLiked) {
  // Act & Assert
  EXPECT_EQ(mojom::ReactionType::kLiked,
            ToggleLikedReactionType(mojom::ReactionType::kDisliked));
}

TEST_F(CatsxpAdsReactionsTypeUtilTest,
       ToggleDislikedReactionTypeFromNeutralToDisliked) {
  // Act & Assert
  EXPECT_EQ(mojom::ReactionType::kDisliked,
            ToggleDislikedReactionType(mojom::ReactionType::kNeutral));
}

TEST_F(CatsxpAdsReactionsTypeUtilTest,
       ToggleDislikedReactionTypeFromDislikedToNeutral) {
  // Act & Assert
  EXPECT_EQ(mojom::ReactionType::kNeutral,
            ToggleDislikedReactionType(mojom::ReactionType::kDisliked));
}

TEST_F(CatsxpAdsReactionsTypeUtilTest,
       ToggleDislikedReactionTypeFromLikedToDisliked) {
  // Act & Assert
  EXPECT_EQ(mojom::ReactionType::kDisliked,
            ToggleDislikedReactionType(mojom::ReactionType::kLiked));
}

}  // namespace catsxp_ads
