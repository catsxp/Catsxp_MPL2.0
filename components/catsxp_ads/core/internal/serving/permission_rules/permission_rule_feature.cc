/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/permission_rule_feature.h"

namespace catsxp_ads {

BASE_FEATURE(kPermissionRulesFeature,
             "PermissionRules",
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace catsxp_ads
