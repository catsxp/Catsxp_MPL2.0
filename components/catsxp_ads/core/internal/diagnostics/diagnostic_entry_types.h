/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_ENTRY_TYPES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_ENTRY_TYPES_H_

namespace catsxp_ads {

// Diagnostic entries should be visually sorted based on the enum order.
enum class DiagnosticEntryType {
  kDeviceId,
  kOptedInToNewTabPageAds,
  kOptedInToNotificationAds,
  kOptedInToSearchResultAds,
  kLanguage,
  kCountry,
  kCatalogId,
  kCatalogLastUpdated,
  kLastUnIdleTime
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_ENTRY_TYPES_H_
