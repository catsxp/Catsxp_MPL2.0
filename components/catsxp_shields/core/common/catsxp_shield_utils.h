/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_CATSXP_SHIELD_UTILS_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_CATSXP_SHIELD_UTILS_H_

#include <map>

#include "catsxp/components/catsxp_shields/core/common/shields_settings.mojom-data-view.h"
#include "components/content_settings/core/common/content_settings.h"

class GURL;

namespace catsxp_shields {

struct ShieldsSettingCounts {
  int allow;
  int standard;
  int aggressive;
};

ContentSetting GetCatsxpFPContentSettingFromRules(
    const ContentSettingsForOneType& fp_rules,
    const GURL& primary_url);

ContentSetting GetCatsxpWebcompatContentSettingFromRules(
    const std::map<ContentSettingsType, ContentSettingsForOneType>&
        webcompat_rules,
    const GURL& primary_url,
    const ContentSettingsType content_settings_type);

ShieldsSettingCounts GetSettingCountFromRules(
    const ContentSettingsForOneType& fp_rules);

ShieldsSettingCounts GetSettingCountFromCosmeticFilteringRules(
    const ContentSettingsForOneType& fp_rules);

mojom::ContentSettingSource ConvertSettingsSource(
    const content_settings::SettingSource source);

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_CATSXP_SHIELD_UTILS_H_
