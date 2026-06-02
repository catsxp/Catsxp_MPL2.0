/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/page_transition_util.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "ui/base/page_transition_types.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsPageTransitionUtilTest, ToUserActivityClickedLinkEventType) {
  // Act & Assert
  EXPECT_EQ(UserActivityEventType::kClickedLink,
            ToUserActivityEventType(ui::PageTransition::PAGE_TRANSITION_LINK));
}

TEST(CatsxpAdsPageTransitionUtilTest, ToUserActivityTypedUrlEventType) {
  // Act & Assert
  EXPECT_EQ(UserActivityEventType::kTypedUrl,
            ToUserActivityEventType(ui::PageTransition::PAGE_TRANSITION_TYPED));
}

TEST(CatsxpAdsPageTransitionUtilTest, ToUserActivityClickedBookmarkEventType) {
  // Act & Assert
  EXPECT_EQ(UserActivityEventType::kClickedBookmark,
            ToUserActivityEventType(
                ui::PageTransition::PAGE_TRANSITION_AUTO_BOOKMARK));
}

TEST(CatsxpAdsPageTransitionUtilTest,
     ToUserActivityTypedAndSelectedNonUrlEventType) {
  // Act & Assert
  EXPECT_EQ(
      UserActivityEventType::kTypedAndSelectedNonUrl,
      ToUserActivityEventType(ui::PageTransition::PAGE_TRANSITION_GENERATED));
}

TEST(CatsxpAdsPageTransitionUtilTest, ToUserActivitySubmittedFormEventType) {
  // Act & Assert
  EXPECT_EQ(
      UserActivityEventType::kSubmittedForm,
      ToUserActivityEventType(ui::PageTransition::PAGE_TRANSITION_FORM_SUBMIT));
}

TEST(CatsxpAdsPageTransitionUtilTest,
     ToUserActivityClickedReloadButtonEventType) {
  // Act & Assert
  EXPECT_EQ(
      UserActivityEventType::kClickedReloadButton,
      ToUserActivityEventType(ui::PageTransition::PAGE_TRANSITION_RELOAD));
}

TEST(CatsxpAdsPageTransitionUtilTest,
     ToUserActivityTypedKeywordOtherThanDefaultSearchProviderEventType) {
  // Act & Assert
  EXPECT_EQ(
      UserActivityEventType::kTypedKeywordOtherThanDefaultSearchProvider,
      ToUserActivityEventType(ui::PageTransition::PAGE_TRANSITION_KEYWORD));
}

TEST(CatsxpAdsPageTransitionUtilTest, ToUserActivityGeneratedKeywordEventType) {
  // Act & Assert
  EXPECT_EQ(UserActivityEventType::kGeneratedKeyword,
            ToUserActivityEventType(
                ui::PageTransition::PAGE_TRANSITION_KEYWORD_GENERATED));
}

}  // namespace catsxp_ads
