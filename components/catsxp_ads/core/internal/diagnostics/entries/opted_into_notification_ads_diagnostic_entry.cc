/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/opted_into_notification_ads_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/internal/common/strings/string_conversions_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

namespace catsxp_ads {

namespace {
constexpr char kName[] = "Opted into notification ads";
}  // namespace

DiagnosticEntryType OptedInToNotificationAdsDiagnosticEntry::GetType() const {
  return DiagnosticEntryType::kOptedInToNotificationAds;
}

std::string OptedInToNotificationAdsDiagnosticEntry::GetName() const {
  return kName;
}

std::string OptedInToNotificationAdsDiagnosticEntry::GetValue() const {
  return BoolToString(UserHasOptedInToNotificationAds());
}

}  // namespace catsxp_ads
