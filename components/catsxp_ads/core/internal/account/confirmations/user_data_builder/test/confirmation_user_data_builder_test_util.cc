/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/user_data_builder/test/confirmation_user_data_builder_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_util.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/test/catalog_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_environment_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

namespace catsxp_ads::test {

namespace {

void MockDiagnosticId() {
  SetProfileStringPrefValue(prefs::kDiagnosticId, kDiagnosticId);
}

}  // namespace

void MockConfirmationUserData() {
  MockDiagnosticId();

  SetUpDeviceId();

  SetCatalogId(kCatalogId);
}

}  // namespace catsxp_ads::test
