/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/studies_user_data.h"

#include <optional>
#include <string_view>
#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/internal/studies/studies_util.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kStudiesKey = "studies";
constexpr std::string_view kTrialNameKey = "name";
constexpr std::string_view kGroupNameKey = "group";

}  // namespace

base::DictValue BuildStudiesUserData() {
  if (!UserHasJoinedCatsxpRewards()) {
    return {};
  }

  base::ListValue list;
  if (const std::optional<base::FieldTrial::ActiveGroup>
          active_field_trial_group = GetActiveFieldTrialStudyGroup()) {
    list.Append(base::DictValue()
                    .Set(kTrialNameKey, active_field_trial_group->trial_name)
                    .Set(kGroupNameKey, active_field_trial_group->group_name));
  }

  return base::DictValue().Set(kStudiesKey, std::move(list));
}

}  // namespace catsxp_ads
