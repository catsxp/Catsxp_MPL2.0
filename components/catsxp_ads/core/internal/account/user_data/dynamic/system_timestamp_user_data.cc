/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/dynamic/system_timestamp_user_data.h"

#include <string_view>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/time/time_formatting_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

namespace catsxp_ads {

namespace {
constexpr std::string_view kSystemTimestampKey = "systemTimestamp";
}  // namespace

base::DictValue BuildSystemTimestampUserData() {
  if (!UserHasJoinedCatsxpRewards()) {
    return {};
  }

  return base::DictValue().Set(
      kSystemTimestampKey, TimeToPrivacyPreservingIso8601(base::Time::Now()));
}

}  // namespace catsxp_ads
