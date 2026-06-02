/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/catalog_last_updated_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/diagnostics/diagnostic_entry_types.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds.*

namespace catsxp_ads {

class CatsxpAdsCatalogLastUpdatedDiagnosticEntryTest : public test::TestBase {};

TEST_F(CatsxpAdsCatalogLastUpdatedDiagnosticEntryTest, CatalogLastUpdated) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("Wed, 18 Nov 1970 12:34:56"));

  SetCatalogLastUpdated(test::Now());

  const CatalogLastUpdatedDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kCatalogLastUpdated,
            diagnostic_entry.GetType());
  EXPECT_EQ("Catalog last updated", diagnostic_entry.GetName());
  EXPECT_EQ("Wednesday, November 18, 1970 at 12:34:56\u202fPM",
            diagnostic_entry.GetValue());
}

TEST_F(CatsxpAdsCatalogLastUpdatedDiagnosticEntryTest, CatalogNeverUpdated) {
  // Arrange
  const CatalogLastUpdatedDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kCatalogLastUpdated,
            diagnostic_entry.GetType());
  EXPECT_EQ("Catalog last updated", diagnostic_entry.GetName());
  EXPECT_THAT(diagnostic_entry.GetValue(), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
