/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/catalog_id_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_util.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/test/catalog_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/diagnostics/diagnostic_entry_types.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds.*

namespace catsxp_ads {

class CatsxpAdsCatalogIdDiagnosticEntryTest : public test::TestBase {};

TEST_F(CatsxpAdsCatalogIdDiagnosticEntryTest, CatalogId) {
  // Arrange
  SetCatalogId(test::kCatalogId);

  const CatalogIdDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kCatalogId, diagnostic_entry.GetType());
  EXPECT_EQ("Catalog ID", diagnostic_entry.GetName());
  EXPECT_EQ(test::kCatalogId, diagnostic_entry.GetValue());
}

TEST_F(CatsxpAdsCatalogIdDiagnosticEntryTest, EmptyCatalogId) {
  // Arrange
  const CatalogIdDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kCatalogId, diagnostic_entry.GetType());
  EXPECT_EQ("Catalog ID", diagnostic_entry.GetName());
  EXPECT_THAT(diagnostic_entry.GetValue(), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
