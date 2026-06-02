/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/opted_into_notification_ads_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/diagnostics/diagnostic_entry_types.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds.*

namespace catsxp_ads {

class CatsxpAdsOptedInToNotificationAdsDiagnosticEntryTest
    : public test::TestBase {};

TEST_F(CatsxpAdsOptedInToNotificationAdsDiagnosticEntryTest, IsOptedIn) {
  // Arrange
  const OptedInToNotificationAdsDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kOptedInToNotificationAds,
            diagnostic_entry.GetType());
  EXPECT_EQ("Opted into notification ads", diagnostic_entry.GetName());
  EXPECT_EQ("true", diagnostic_entry.GetValue());
}

TEST_F(CatsxpAdsOptedInToNotificationAdsDiagnosticEntryTest, IsOptedOut) {
  // Arrange
  test::OptOutOfNotificationAds();

  const OptedInToNotificationAdsDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kOptedInToNotificationAds,
            diagnostic_entry.GetType());
  EXPECT_EQ("Opted into notification ads", diagnostic_entry.GetName());
  EXPECT_EQ("false", diagnostic_entry.GetValue());
}

}  // namespace catsxp_ads
