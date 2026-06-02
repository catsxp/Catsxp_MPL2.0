/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/site_visit/site_visit_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "net/http/http_status_code.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSiteVisitUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsSiteVisitUtilTest,
       AllowNewTabPageAdPageLandIfRewardsUserAndOptedInToNewTabPageAds) {
  // Act & Assert
  EXPECT_TRUE(IsAllowedToLandOnPage(mojom::AdType::kNewTabPageAd));
}

TEST_F(CatsxpAdsSiteVisitUtilTest,
       DoNotAllowNewTabPageAdPageLandIfRewardsUserAndOptedOutOfNewTabPageAds) {
  // Arrange
  test::OptOutOfNewTabPageAds();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kNewTabPageAd));
}

TEST_F(
    CatsxpAdsSiteVisitUtilTest,
    DoNotAllowNewTabPageAdPageLandIfNonRewardsUserAndOptedInToNewTabPageAds) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kNewTabPageAd));
}

TEST_F(
    CatsxpAdsSiteVisitUtilTest,
    DoNotAllowNewTabPageAdPageLandIfNonRewardsUserAndOptedOutOfNewTabPageAds) {
  // Arrange
  test::DisableCatsxpRewards();
  test::OptOutOfNewTabPageAds();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kNewTabPageAd));
}

TEST_F(CatsxpAdsSiteVisitUtilTest,
       AllowNotificationAdPageLandIfRewardsUserAndOptedInToNotificationAds) {
  // Act & Assert
  EXPECT_TRUE(IsAllowedToLandOnPage(mojom::AdType::kNotificationAd));
}

TEST_F(
    CatsxpAdsSiteVisitUtilTest,
    DoNotAllowNotificationAdPageLandIfRewardsUserAndOptedOutOfNotificationAds) {
  // Arrange
  test::OptOutOfNotificationAds();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kNotificationAd));
}

TEST_F(CatsxpAdsSiteVisitUtilTest,
       DoNotAllowNotificationAdPageLandIfNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kNotificationAd));
}

TEST_F(CatsxpAdsSiteVisitUtilTest,
       AllowSearchResultAdPageLandIfRewardsUserAndOptedInToSearchResultAds) {
  // Act & Assert
  EXPECT_TRUE(IsAllowedToLandOnPage(mojom::AdType::kSearchResultAd));
}

TEST_F(
    CatsxpAdsSiteVisitUtilTest,
    DoNotAllowSearchResultAdPageLandIfRewardsUserAndOptedOutOfSearchResultAds) {
  // Arrange
  test::OptOutOfSearchResultAds();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kSearchResultAd));
}

TEST_F(
    CatsxpAdsSiteVisitUtilTest,
    DoNotAllowSearchResultAdPageLandIfNonRewardsUserAndOptedInToSearchResultAds) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kSearchResultAd));
}

TEST_F(CatsxpAdsSiteVisitUtilTest, ShouldResumePageLand) {
  // Arrange
  ads_client_notifier_.NotifyBrowserDidBecomeActive();
  ads_client_notifier_.NotifyBrowserDidEnterForeground();

  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  // Act & Assert
  EXPECT_TRUE(ShouldResumePageLand(/*tab_id=*/1));
}

TEST_F(CatsxpAdsSiteVisitUtilTest, ShouldNotResumePageLandIfTabIsOccluded) {
  // Arrange
  ads_client_notifier_.NotifyBrowserDidBecomeActive();
  ads_client_notifier_.NotifyBrowserDidEnterForeground();

  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);
  tab_helper_.OpenTab(
      /*tab_id=*/2,
      /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
      net::HTTP_OK);

  // Act & Assert
  EXPECT_FALSE(ShouldResumePageLand(/*tab_id=*/1));
}

TEST_F(CatsxpAdsSiteVisitUtilTest, ShouldNotResumePageLandIfBrowserIsInactive) {
  // Arrange
  ads_client_notifier_.NotifyBrowserDidResignActive();
  ads_client_notifier_.NotifyBrowserDidEnterForeground();

  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  // Act & Assert
  EXPECT_FALSE(ShouldResumePageLand(/*tab_id=*/1));
}

TEST_F(CatsxpAdsSiteVisitUtilTest,
       ShouldNotResumePageLandIfBrowserDidEnterBackground) {
  // Arrange
  ads_client_notifier_.NotifyBrowserDidBecomeActive();
  ads_client_notifier_.NotifyBrowserDidEnterBackground();

  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  // Act & Assert
  EXPECT_FALSE(ShouldResumePageLand(/*tab_id=*/1));
}

TEST_F(CatsxpAdsSiteVisitUtilTest, DidLandOnPage) {
  // Arrange
  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  // Act & Assert
  EXPECT_TRUE(DidLandOnPage(/*tab_id=*/1, GURL("https://catsxp.com")));
}

TEST_F(CatsxpAdsSiteVisitUtilTest, DoNotLandOnPageForClosedTab) {
  // Arrange
  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  ads_client_notifier_.NotifyDidCloseTab(/*tab_id=*/1);

  // Act & Assert
  EXPECT_FALSE(DidLandOnPage(/*tab_id=*/1, GURL("https://catsxp.com")));
}

TEST_F(CatsxpAdsSiteVisitUtilTest, DoNotLandOnPageForDomainOrHostMismatch) {
  // Arrange
  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://foo.com")}, net::HTTP_OK);

  // Act & Assert
  EXPECT_FALSE(DidLandOnPage(/*tab_id=*/1, GURL("https://catsxp.com")));
}

}  // namespace catsxp_ads
