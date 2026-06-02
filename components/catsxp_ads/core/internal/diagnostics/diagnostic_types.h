/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

// DiagnosticMap type alias separated from DiagnosticManager so that consumers
// needing only the map type do not pull in ads_callback.h.

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_TYPES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_TYPES_H_

#include <memory>

#include "base/containers/flat_map.h"
#include "catsxp/components/catsxp_ads/core/internal/diagnostics/diagnostic_entry_types.h"
#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/diagnostic_entry_interface.h"

namespace catsxp_ads {

using DiagnosticMap = base::flat_map<DiagnosticEntryType,
                                     std::unique_ptr<DiagnosticEntryInterface>>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_TYPES_H_
