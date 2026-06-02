/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_CONSTANTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_CONSTANTS_H_

#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

inline constexpr char kTraceEventCategory[] = "catsxp.ads";

inline constexpr char kDatabaseFilename[] = "database.sqlite";

// TODO(https://github.com/catsxp/catsxp-browser/issues/39795): Transition away
// from using JSON state to a more efficient data approach.
inline constexpr char kClientJsonFilename[] = "client.json";

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_CONSTANTS_H_
