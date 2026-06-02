/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_RESOURCE_ANTI_TARGETING_RESOURCE_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_RESOURCE_ANTI_TARGETING_RESOURCE_INFO_H_

#include <map>
#include <optional>
#include <set>
#include <string>

#include "base/values.h"

class GURL;

namespace catsxp_ads {

using AntiTargetingSiteList = std::set<GURL>;
using AntiTargetingCreativeSetMap =
    std::map</*creative_set_id*/ std::string, AntiTargetingSiteList>;

struct AntiTargetingResourceInfo final {
  AntiTargetingResourceInfo();

  AntiTargetingResourceInfo(const AntiTargetingResourceInfo&) = delete;
  AntiTargetingResourceInfo& operator=(const AntiTargetingResourceInfo&) =
      delete;

  AntiTargetingResourceInfo(AntiTargetingResourceInfo&&) noexcept;
  AntiTargetingResourceInfo& operator=(AntiTargetingResourceInfo&&) noexcept;

  ~AntiTargetingResourceInfo();

  static std::optional<AntiTargetingResourceInfo> MaybeFromDict(
      base::DictValue dict);

  std::optional<int> version;
  AntiTargetingCreativeSetMap creative_sets;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_RESOURCE_ANTI_TARGETING_RESOURCE_INFO_H_
