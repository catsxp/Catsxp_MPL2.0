/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_PERMISSION_RULES_BASE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_PERMISSION_RULES_BASE_H_

namespace catsxp_ads {

class PermissionRulesBase {
 public:
  PermissionRulesBase(const PermissionRulesBase&) = delete;
  PermissionRulesBase& operator=(const PermissionRulesBase&) = delete;

  virtual ~PermissionRulesBase();

 protected:
  PermissionRulesBase();

  static bool HasPermission();
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_PERMISSION_RULES_BASE_H_
