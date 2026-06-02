/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/country_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/diagnostics/diagnostic_entry_types.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds.*

namespace catsxp_ads {

class CatsxpAdsCountryDiagnosticEntryTest : public test::TestBase {};

TEST_F(CatsxpAdsCountryDiagnosticEntryTest, GetValue) {
  // Arrange
  fake_locale_.SetCountryCode("KY");

  const CountryDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kCountry, diagnostic_entry.GetType());
  EXPECT_EQ("Country", diagnostic_entry.GetName());
  EXPECT_EQ("KY", diagnostic_entry.GetValue());
}

}  // namespace catsxp_ads
