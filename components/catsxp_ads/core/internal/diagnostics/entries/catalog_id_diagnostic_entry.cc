/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/catalog_id_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_util.h"

namespace catsxp_ads {

namespace {
constexpr char kName[] = "Catalog ID";
}  // namespace

DiagnosticEntryType CatalogIdDiagnosticEntry::GetType() const {
  return DiagnosticEntryType::kCatalogId;
}

std::string CatalogIdDiagnosticEntry::GetName() const {
  return kName;
}

std::string CatalogIdDiagnosticEntry::GetValue() const {
  return GetCatalogId();
}

}  // namespace catsxp_ads
