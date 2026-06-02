/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/permission_rules_base.h"

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/command_line_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/confirmation_tokens_permission_rule.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/issuers_permission_rule.h"

namespace catsxp_ads {

PermissionRulesBase::PermissionRulesBase() = default;

PermissionRulesBase::~PermissionRulesBase() = default;

// static
bool PermissionRulesBase::HasPermission() {
  if (!HasIssuersPermission()) {
    return false;
  }

  if (!HasConfirmationTokensPermission()) {
    return false;
  }

  if (!HasCommandLinePermission()) {
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
