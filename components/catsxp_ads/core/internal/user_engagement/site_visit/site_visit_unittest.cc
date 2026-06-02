/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/site_visit/site_visit.h"

#include <cstdint>
#include <memory>
#include <vector>

#include "base/test/run_until.h"
#include "base/test/scoped_feature_list.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/site_visit/site_visit_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/site_visit/test/site_visit_observer_mock.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "net/http/http_status_code.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSiteVisitTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    site_visit_ = std::make_unique<SiteVisit>();
    site_visit_->AddObserver(&site_visit_observer_mock_);

    ads_client_notifier_.NotifyBrowserDidEnterForeground();
    ads_client_notifier_.NotifyBrowserDidBecomeActive();
  }

  void TearDown() override {
    site_visit_->RemoveObserver(&site_visit_observer_mock_);

    test::TestBase::TearDown();
  }

  void SimulateClickingAd(const AdInfo& ad,
                          int32_t tab_id,
                          const std::vector<GURL>& redirect_chain,
                          int http_status_code) {
    site_visit_->set_last_clicked_ad(ad);

    tab_helper_.OpenTab(tab_id, redirect_chain, http_status_code);
  }

  std::unique_ptr<SiteVisit> site_visit_;
  SiteVisitObserverMock site_visit_observer_mock_;

  ::testing::InSequence s_;
};

TEST_F(CatsxpAdsSiteVisitTest, LandOnNewTabPageAdPage) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNewTabPageAd,
                                  /*use_random_uuids=*/true);
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidLandOnPage(/*tab_id=*/1, net::HTTP_OK, ad));
  FastForwardClockBy(kPageLandAfter.Get());
}

TEST_F(CatsxpAdsSiteVisitTest,
       DoNotLandOnNewTabPageAdPageIfOptedOutOfNewTabPageAds) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  test::OptOutOfNewTabPageAds();

  const AdInfo ad = test::BuildAd(mojom::AdType::kNewTabPageAd,
                                  /*use_random_uuids=*/true);
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage).Times(0);
  FastForwardClockBy(kPageLandAfter.Get());
}

TEST_F(CatsxpAdsSiteVisitTest, DoNotLandOnNewTabPageAdPageForNonRewardsUser) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  test::DisableCatsxpRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kNewTabPageAd,
                                  /*use_random_uuids=*/true);
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage).Times(0);
  FastForwardClockBy(kPageLandAfter.Get());
}

TEST_F(CatsxpAdsSiteVisitTest, LandOnNotificationAdPage) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidLandOnPage(/*tab_id=*/1, net::HTTP_OK, ad));
  FastForwardClockBy(kPageLandAfter.Get());
}

TEST_F(CatsxpAdsSiteVisitTest,
       DoNotLandOnNotificationAdPageIfOptedOutOfNotificationAds) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  test::OptOutOfNotificationAds();

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage).Times(0);
  FastForwardClockBy(kPageLandAfter.Get());
}

TEST_F(CatsxpAdsSiteVisitTest, DoNotLandOnNotificationAdPageForNonRewardsUser) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  test::DisableCatsxpRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage).Times(0);
  FastForwardClockBy(kPageLandAfter.Get());
}

TEST_F(CatsxpAdsSiteVisitTest,
       DoNotLandOnPageIfTheRedirectChainDoesNotMatchTheLastClickedAd) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  SimulateClickingAd(
      ad, /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
      net::HTTP_OK);

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage).Times(0);
  FastForwardClockBy(kPageLandAfter.Get());
}

TEST_F(CatsxpAdsSiteVisitTest, DoNotLandOnPageIfTheSameTabIsAlreadyLanding) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  EXPECT_CALL(site_visit_observer_mock_,
              OnMaybeLandOnPage(ad, /*after=*/kPageLandAfter.Get()));
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);

  tab_helper_.NavigateToUrl(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com/about")}, net::HTTP_OK);
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage(
                                             /*tab_id=*/1, net::HTTP_OK, ad));
  FastForwardClockBy(kPageLandAfter.Get());
}

TEST_F(
    CatsxpAdsSiteVisitTest,
    SuspendPageLandWhenTabBecomesOccludedThenResumePageLandWhenTabBecomesVisible) {
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kSiteVisitFeature, {{"page_land_after", "10s"}});

  // Tab 1 (Visible/Start page landing)
  const AdInfo ad_1 = test::BuildAd(mojom::AdType::kNotificationAd,
                                    /*use_random_uuids=*/true);
  EXPECT_CALL(site_visit_observer_mock_,
              OnMaybeLandOnPage(ad_1, /*after=*/kPageLandAfter.Get()));
  SimulateClickingAd(ad_1, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Tab 1 (Occluded/Suspend page landing)
  AdvanceClockBy(kPageLandAfter.Get() - base::Seconds(3));
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidSuspendPageLand(
                  /*tab_id=*/1,
                  /*remaining_time=*/base::Seconds(3)));

  // Tab 2 (Visible/Start page landing)
  const AdInfo ad_2 = test::BuildAd(mojom::AdType::kNotificationAd,
                                    /*use_random_uuids=*/true);
  EXPECT_CALL(site_visit_observer_mock_,
              OnMaybeLandOnPage(ad_2, /*after=*/kPageLandAfter.Get()));
  SimulateClickingAd(ad_2, /*tab_id=*/2,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Tab 2 (Occluded/Suspend page landing)
  AdvanceClockBy(kPageLandAfter.Get() - base::Seconds(7));
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidSuspendPageLand(
                  /*tab_id=*/2,
                  /*remaining_time=*/base::Seconds(7)));

  // Tab 1 (Visible/Resume page landing)
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidResumePageLand(
                  /*tab_id=*/1,
                  /*remaining_time=*/base::Seconds(3)));
  tab_helper_.SelectTab(/*tab_id=*/1);
  ASSERT_EQ(1U, GetPendingTaskCount());

  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage(
                                             /*tab_id=*/1, net::HTTP_OK, ad_1));
  FastForwardClockToNextPendingTask();

  // Tab 1 (Occluded)
  EXPECT_CALL(site_visit_observer_mock_, OnDidSuspendPageLand).Times(0);

  // Tab 2 (Visible/Resume page landing)
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidResumePageLand(
                  /*tab_id=*/2,
                  /*remaining_time=*/base::Seconds(7)));
  tab_helper_.SelectTab(/*tab_id=*/2);
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage(
                                             /*tab_id=*/2, net::HTTP_OK, ad_2));
  FastForwardClockToNextPendingTask();
  EXPECT_FALSE(HasPendingTasks());
}

TEST_F(
    CatsxpAdsSiteVisitTest,
    SuspendPageLandWhenBrowserEntersBackgroundThenResumePageLandWhenBrowserEntersForeground) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  // Tab 1 (Start page landing)
  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  EXPECT_CALL(site_visit_observer_mock_,
              OnMaybeLandOnPage(ad, /*after=*/kPageLandAfter.Get()));
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Browser (Entered background/Suspend page landing)
  AdvanceClockBy(kPageLandAfter.Get() - base::Seconds(3));

  EXPECT_CALL(site_visit_observer_mock_,
              OnDidSuspendPageLand(
                  /*tab_id=*/1,
                  /*remaining_time=*/base::Seconds(3)));
  ads_client_notifier_.NotifyBrowserDidEnterBackground();
  ASSERT_FALSE(HasPendingTasks());

  // Tab 1 (Entered foreground/Resume page landing)
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidResumePageLand(
                  /*tab_id=*/1,
                  /*remaining_time=*/base::Seconds(3)));
  ads_client_notifier_.NotifyBrowserDidEnterForeground();
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage(
                                             /*tab_id=*/1, net::HTTP_OK, ad));
  FastForwardClockToNextPendingTask();
  EXPECT_FALSE(HasPendingTasks());
}

TEST_F(
    CatsxpAdsSiteVisitTest,
    SuspendPageLandWhenBrowserResignsActiveThenResumePageLandWhenBrowserBecomesActive) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  // Tab 1 (Start page landing)
  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  EXPECT_CALL(site_visit_observer_mock_,
              OnMaybeLandOnPage(ad, /*after=*/kPageLandAfter.Get()));
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Browser (Resign active/Suspend page landing)
  AdvanceClockBy(kPageLandAfter.Get() - base::Seconds(3));

  EXPECT_CALL(site_visit_observer_mock_,
              OnDidSuspendPageLand(
                  /*tab_id=*/1,
                  /*remaining_time=*/base::Seconds(3)));
  ads_client_notifier_.NotifyBrowserDidResignActive();
  ASSERT_FALSE(HasPendingTasks());

  // Tab 1 (Become active/Resume page landing)
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidResumePageLand(
                  /*tab_id=*/1,
                  /*remaining_time=*/base::Seconds(3)));
  ads_client_notifier_.NotifyBrowserDidBecomeActive();
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage(
                                             /*tab_id=*/1, net::HTTP_OK, ad));
  FastForwardClockToNextPendingTask();
  EXPECT_FALSE(HasPendingTasks());
}

TEST_F(CatsxpAdsSiteVisitTest, DoNotSuspendOrResumePageLand) {
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kSiteVisitFeature, {{"should_suspend_and_resume_page_land", "false"}});

  // Tab (Start page landing)
  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  EXPECT_CALL(site_visit_observer_mock_,
              OnMaybeLandOnPage(ad, /*after=*/kPageLandAfter.Get()));
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Browser (Resign active/Suspend page landing)
  AdvanceClockBy(kPageLandAfter.Get() - base::Seconds(3));

  EXPECT_CALL(site_visit_observer_mock_, OnDidSuspendPageLand).Times(0);
  ads_client_notifier_.NotifyBrowserDidResignActive();
  ASSERT_TRUE(HasPendingTasks());

  // Tab (Become active/Resume page landing)
  EXPECT_CALL(site_visit_observer_mock_, OnDidResumePageLand).Times(0);
  ads_client_notifier_.NotifyBrowserDidBecomeActive();
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage(
                                             /*tab_id=*/1, net::HTTP_OK, ad));
  FastForwardClockToNextPendingTask();
  EXPECT_FALSE(HasPendingTasks());
}

TEST_F(
    CatsxpAdsSiteVisitTest,
    DoNotLandOnPageIfTheTabIsVisibleAndTheRedirectChainMatchesTheLastClickedAdForNonRewardsUser) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  test::DisableCatsxpRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnMaybeLandOnPage).Times(0);
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);
  EXPECT_EQ(0U, GetPendingTaskCount());
}

TEST_F(CatsxpAdsSiteVisitTest,
       LandOnPagesForMultipleSiteVisitsOccurringAtTheSameTime) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  // Tab 1 (Visible/Start page landing)
  const AdInfo ad_1 = test::BuildAd(mojom::AdType::kNotificationAd,
                                    /*use_random_uuids=*/true);
  EXPECT_CALL(site_visit_observer_mock_,
              OnMaybeLandOnPage(ad_1, /*after=*/kPageLandAfter.Get()));
  SimulateClickingAd(ad_1, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Tab 1 (Occluded/Suspend page landing)
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidSuspendPageLand(
                  /*tab_id=*/1, kPageLandAfter.Get()));

  // Tab 2 (Visible/Start page landing)
  const AdInfo ad_2 = test::BuildAd(mojom::AdType::kNotificationAd,
                                    /*use_random_uuids=*/true);
  EXPECT_CALL(site_visit_observer_mock_,
              OnMaybeLandOnPage(ad_2, /*after=*/kPageLandAfter.Get()));
  SimulateClickingAd(ad_2, /*tab_id=*/2,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Tab 2 (Occluded/Suspend page landing)
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidSuspendPageLand(/*tab_id=*/2, kPageLandAfter.Get()));

  // Tab 1 (Visible/Resume page landing)
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidResumePageLand(/*tab_id=*/1, kPageLandAfter.Get()));
  tab_helper_.SelectTab(/*tab_id=*/1);
  ASSERT_EQ(1U, GetPendingTaskCount());

  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage(
                                             /*tab_id=*/1, net::HTTP_OK, ad_1));
  FastForwardClockToNextPendingTask();

  // Tab 2 (Visible/Resume page landing)
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidResumePageLand(
                  /*tab_id=*/2, kPageLandAfter.Get()));
  tab_helper_.SelectTab(/*tab_id=*/2);
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage(
                                             /*tab_id=*/2, net::HTTP_OK, ad_2));
  FastForwardClockToNextPendingTask();

  EXPECT_FALSE(HasPendingTasks());
}

TEST_F(
    CatsxpAdsSiteVisitTest,
    LandOnPageIfTheTabIsVisibleAndTheRedirectChainMatchesTheLastClickedAdForHttpSuccessfulResponseStatusCode) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  EXPECT_CALL(site_visit_observer_mock_,
              OnMaybeLandOnPage(ad, /*after=*/kPageLandAfter.Get()));
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);
  ASSERT_EQ(1U, GetPendingTaskCount());

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage(
                                             /*tab_id=*/1, net::HTTP_OK, ad));
  FastForwardClockBy(kPageLandAfter.Get());
}

TEST_F(
    CatsxpAdsSiteVisitTest,
    LandOnPageIfTheTabIsVisibleAndTheRedirectChainMatchesTheLastClickedAdForHttpClientErrorResponseStatusCode) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  EXPECT_CALL(site_visit_observer_mock_,
              OnMaybeLandOnPage(ad, /*after=*/kPageLandAfter.Get()))
      .Times(0);

  // Act
  bool did_land_on_page = false;
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidLandOnPage(/*tab_id=*/1, net::HTTP_BAD_REQUEST, ad))
      .WillOnce([&] { did_land_on_page = true; });
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_BAD_REQUEST);

  // Assert
  ASSERT_TRUE(base::test::RunUntil([&] { return did_land_on_page; }));
}

TEST_F(
    CatsxpAdsSiteVisitTest,
    LandOnPageIfTheTabIsVisibleAndTheRedirectChainMatchesTheLastClickedAdForHttpServerErrorResponseStatusCode) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  EXPECT_CALL(site_visit_observer_mock_,
              OnMaybeLandOnPage(ad, /*after=*/kPageLandAfter.Get()))
      .Times(0);

  // Act
  bool did_land_on_page = false;
  EXPECT_CALL(site_visit_observer_mock_,
              OnDidLandOnPage(
                  /*tab_id=*/1, net::HTTP_INTERNAL_SERVER_ERROR, ad))
      .WillOnce([&] { did_land_on_page = true; });
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_INTERNAL_SERVER_ERROR);

  // Assert
  ASSERT_TRUE(base::test::RunUntil([&] { return did_land_on_page; }));
}

TEST_F(CatsxpAdsSiteVisitTest, DoNotLandOnPageIfTheTabIsOccluded) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage).Times(0);
  ads_client_notifier_.NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://catsxp.com")},
      /*is_new_navigation=*/false, /*is_restoring=*/false,
      /*is_visible=*/false);
  FastForwardClockBy(kPageLandAfter.Get());
}

TEST_F(
    CatsxpAdsSiteVisitTest,
    DoNotLandOnPageIfTheVisibleTabRedirectChainDoesNotMatchTheLastClickedAd) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  SimulateClickingAd(
      ad, /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
      net::HTTP_OK);

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage).Times(0);
  FastForwardClockBy(kPageLandAfter.Get());
}

TEST_F(CatsxpAdsSiteVisitTest,
       CancelPageLandIfTheRedirectChainNoLongerMatchesTheAdTargetUrl) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnCanceledPageLand(/*tab_id=*/1, ad));
  tab_helper_.NavigateToUrl(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
      net::HTTP_OK);
  FastForwardClockBy(kPageLandAfter.Get());
}

TEST_F(CatsxpAdsSiteVisitTest, CancelPageLandIfTheTabIsClosed) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  SimulateClickingAd(ad, /*tab_id=*/1,
                     /*redirect_chain=*/{GURL("https://catsxp.com")},
                     net::HTTP_OK);

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnCanceledPageLand(/*tab_id=*/1, ad));
  tab_helper_.CloseTab(/*tab_id=*/1);
}

TEST_F(CatsxpAdsSiteVisitTest,
       PageLandIsNotRecordedWhenNavigationCommitsBeforeLastClickedAdIsSet) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kSiteVisitFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);

  // Open the tab before setting `last_clicked_ad`. `MaybeLandOnPage` evaluates
  // `last_clicked_ad` at the moment the tab opens, so the page land timer is
  // never started and no land is recorded. This documents the ordering contract
  // that event handlers must satisfy by calling `OnWillFireAdClickedEvent`
  // synchronously before any asynchronous database write.
  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);
  site_visit_->set_last_clicked_ad(ad);

  // Act & Assert
  EXPECT_CALL(site_visit_observer_mock_, OnDidLandOnPage).Times(0);
  FastForwardClockBy(kPageLandAfter.Get());
}

}  // namespace catsxp_ads
