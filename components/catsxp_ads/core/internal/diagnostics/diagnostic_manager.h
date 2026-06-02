/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_MANAGER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_MANAGER_H_

#include <memory>

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/diagnostic_types.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads {

class DiagnosticManager final {
 public:
  DiagnosticManager();

  DiagnosticManager(const DiagnosticManager&) = delete;
  DiagnosticManager& operator=(const DiagnosticManager&) = delete;

  ~DiagnosticManager();

  static DiagnosticManager& GetInstance();

  void SetEntry(std::unique_ptr<DiagnosticEntryInterface> entry);

  void GetDiagnostics(GetDiagnosticsCallback callback) const;

 private:
  DiagnosticMap diagnostics_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_MANAGER_H_
