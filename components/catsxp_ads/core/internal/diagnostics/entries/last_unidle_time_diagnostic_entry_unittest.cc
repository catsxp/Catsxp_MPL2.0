/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/last_unidle_time_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/diagnostics/diagnostic_entry_types.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds.*

namespace catsxp_ads {

class CatsxpAdsLastUnIdleTimeDiagnosticEntryTest : public test::TestBase {};

TEST_F(CatsxpAdsLastUnIdleTimeDiagnosticEntryTest, LastUnIdleTime) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("Mon, 8 July 1996 12:34:56"));

  LastUnIdleTimeDiagnosticEntry diagnostic_entry(test::Now());

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kLastUnIdleTime, diagnostic_entry.GetType());
  EXPECT_EQ("Last unidle time", diagnostic_entry.GetName());
  EXPECT_EQ("Monday, July 8, 1996 at 12:34:56\u202fPM",
            diagnostic_entry.GetValue());
}

TEST_F(CatsxpAdsLastUnIdleTimeDiagnosticEntryTest, WasNeverUnIdle) {
  // Arrange
  const LastUnIdleTimeDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kLastUnIdleTime, diagnostic_entry.GetType());
  EXPECT_EQ("Last unidle time", diagnostic_entry.GetName());
  EXPECT_EQ("Never", diagnostic_entry.GetValue());
}

}  // namespace catsxp_ads
