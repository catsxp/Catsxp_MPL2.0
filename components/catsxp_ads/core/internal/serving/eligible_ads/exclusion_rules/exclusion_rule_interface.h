/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULE_INTERFACE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULE_INTERFACE_H_

#include <string>

namespace catsxp_ads {

template <typename T>
class ExclusionRuleInterface {
 public:
  virtual ~ExclusionRuleInterface() = default;

  // Return a unique cache key for the given creative ad.
  virtual std::string GetCacheKey(const T&) const = 0;

  // Returns whether the given creative ad should be included based on the
  // exclusion rule.
  virtual bool ShouldInclude(const T&) const = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULE_INTERFACE_H_
