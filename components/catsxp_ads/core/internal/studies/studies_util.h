/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_STUDIES_STUDIES_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_STUDIES_STUDIES_UTIL_H_

#include <optional>

#include "base/metrics/field_trial.h"

namespace catsxp_ads {

std::optional<base::FieldTrial::ActiveGroup> GetActiveFieldTrialStudyGroup();

void LogActiveFieldTrialStudyGroups();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_STUDIES_STUDIES_UTIL_H_
