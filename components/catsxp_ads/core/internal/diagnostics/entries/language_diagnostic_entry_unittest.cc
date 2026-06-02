/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/language_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/diagnostics/diagnostic_entry_types.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds.*

namespace catsxp_ads {

class CatsxpAdsLanguageDiagnosticEntryTest : public test::TestBase {};

TEST_F(CatsxpAdsLanguageDiagnosticEntryTest, GetValue) {
  // Arrange
  const LanguageDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kLanguage, diagnostic_entry.GetType());
  EXPECT_EQ("Language", diagnostic_entry.GetName());
  EXPECT_EQ("en", diagnostic_entry.GetValue());
}

}  // namespace catsxp_ads
