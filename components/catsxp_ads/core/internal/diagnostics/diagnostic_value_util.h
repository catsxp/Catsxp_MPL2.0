/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_VALUE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_VALUE_UTIL_H_

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/diagnostics/diagnostic_types.h"

namespace catsxp_ads {

base::ListValue DiagnosticsToList(const DiagnosticMap& diagnostics);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_VALUE_UTIL_H_
