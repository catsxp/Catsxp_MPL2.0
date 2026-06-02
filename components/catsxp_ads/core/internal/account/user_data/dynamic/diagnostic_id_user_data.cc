/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/dynamic/diagnostic_id_user_data.h"

#include <string>
#include <string_view>

#include "base/uuid.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

namespace catsxp_ads {

namespace {
constexpr std::string_view kDiagnosticIdKey = "diagnosticId";
}  // namespace

base::DictValue BuildDiagnosticIdUserData() {
  if (!UserHasJoinedCatsxpRewards()) {
    return {};
  }

  const std::string diagnostic_id = GetProfileStringPref(prefs::kDiagnosticId);

  const base::Uuid uuid = base::Uuid::ParseCaseInsensitive(diagnostic_id);
  if (!uuid.is_valid()) {
    // Invalid diagnotic id.
    return {};
  }

  return base::DictValue().Set(kDiagnosticIdKey, diagnostic_id);
}

}  // namespace catsxp_ads
