/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/device_id_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_environment_util.h"
#include "catsxp/components/catsxp_ads/core/internal/diagnostics/diagnostic_entry_types.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds.*

namespace catsxp_ads {

class CatsxpAdsDeviceIdDiagnosticEntryTest : public test::TestBase {};

TEST_F(CatsxpAdsDeviceIdDiagnosticEntryTest, GetValue) {
  // Arrange
  test::SetUpDeviceId();

  const DeviceIdDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kDeviceId, diagnostic_entry.GetType());
  EXPECT_EQ("Device Id", diagnostic_entry.GetName());
  EXPECT_EQ(test::kDeviceId, diagnostic_entry.GetValue());
}

}  // namespace catsxp_ads
