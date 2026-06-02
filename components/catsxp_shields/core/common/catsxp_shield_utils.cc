/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/core/common/catsxp_shield_utils.h"

#include <map>

#include "base/containers/map_util.h"
#include "base/feature_list.h"
#include "base/no_destructor.h"
#include "base/notreached.h"
#include "base/strings/string_util.h"
#include "catsxp/components/catsxp_shields/core/common/catsxp_shields_settings_values.h"
#include "catsxp/components/catsxp_shields/core/common/shields_settings.mojom-data-view.h"
#include "catsxp/components/webcompat/core/common/features.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "url/gurl.h"

namespace catsxp_shields {

ContentSetting GetCatsxpFPContentSettingFromRules(
    const ContentSettingsForOneType& fp_rules,
    const GURL& primary_url) {
  static const base::NoDestructor<ContentSettingsPattern> kBalancedRule(
      ContentSettingsPattern::FromString("https://balanced"));
  ContentSettingPatternSource fp_rule;
  for (const auto& rule : fp_rules) {
    if (rule.secondary_pattern == *kBalancedRule) {
      continue;
    }
    if (rule.primary_pattern.Matches(primary_url)) {
      return rule.GetContentSetting();
    }
  }

  return CONTENT_SETTING_DEFAULT;
}

ContentSetting GetCatsxpWebcompatContentSettingFromRules(
    const std::map<ContentSettingsType, ContentSettingsForOneType>&
        webcompat_rules,
    const GURL& primary_url,
    const ContentSettingsType content_settings_type) {
  if (!base::FeatureList::IsEnabled(
          webcompat::features::kCatsxpWebcompatExceptionsService)) {
    return CONTENT_SETTING_DEFAULT;
  }
  const auto* rules = base::FindOrNull(webcompat_rules, content_settings_type);
  if (!rules) {
    return CONTENT_SETTING_DEFAULT;
  }
  for (const auto& rule : *rules) {
    if (rule.primary_pattern.Matches(primary_url)) {
      return rule.GetContentSetting();
    }
  }
  return CONTENT_SETTING_DEFAULT;
}

ShieldsSettingCounts GetSettingCountFromRules(
    const ContentSettingsForOneType& fp_rules) {
  ShieldsSettingCounts result = {};

  for (const auto& rule : fp_rules) {
    if (rule.primary_pattern.MatchesAllHosts()) {
      continue;
    }
    if (rule.GetContentSetting() == CONTENT_SETTING_ALLOW) {
      result.allow++;
    } else if (rule.GetContentSetting() == CONTENT_SETTING_BLOCK) {
      result.aggressive++;
    } else {
      result.standard++;
    }
  }

  return result;
}

ShieldsSettingCounts GetSettingCountFromCosmeticFilteringRules(
    const ContentSettingsForOneType& fp_rules) {
  ShieldsSettingCounts result = {};

  for (const auto& rule : fp_rules) {
    if (rule.primary_pattern.MatchesAllHosts()) {
      continue;
    }
    switch (CosmeticFilteringSetting::FromValue(rule.setting_value)) {
      case ControlType::ALLOW:
        ++result.allow;
        break;
      case ControlType::BLOCK:
        ++result.aggressive;
        break;
      default:
        ++result.standard;
    }
  }

  return result;
}

mojom::ContentSettingSource ConvertSettingsSource(
    const content_settings::SettingSource source) {
  switch (source) {
    case content_settings::SettingSource::kUser:
      return mojom::ContentSettingSource::kUser;
    case content_settings::SettingSource::kExtension:
      return mojom::ContentSettingSource::kExtension;
    case content_settings::SettingSource::kPolicy:
      return mojom::ContentSettingSource::kPolicy;
    case content_settings::SettingSource::kSupervised:
      return mojom::ContentSettingSource::kSupervised;
    case content_settings::SettingSource::kInstalledWebApp:
      return mojom::ContentSettingSource::kInstalledWebApp;
    case content_settings::SettingSource::kNone:
      return mojom::ContentSettingSource::kNone;
    case content_settings::SettingSource::kAllowList:
      return mojom::ContentSettingSource::kAllowList;
    case content_settings::SettingSource::kRemoteList:
      return mojom::ContentSettingSource::kRemoteList;
    case content_settings::SettingSource::kOsJavascriptOptimizer:
      return mojom::ContentSettingSource::kOsJavascriptOptimizer;
    case content_settings::SettingSource::kTest:
      return mojom::ContentSettingSource::kTest;
  }
  NOTREACHED();
}

}  // namespace catsxp_shields
