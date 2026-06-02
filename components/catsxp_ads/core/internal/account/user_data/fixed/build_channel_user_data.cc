/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/build_channel_user_data.h"

#include <string_view>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"

namespace catsxp_ads {

namespace {
constexpr std::string_view kBuildChannelKey = "buildChannel";
}  // namespace

base::DictValue BuildBuildChannelUserData() {
  const auto& build_channel = GlobalState::GetInstance()->BuildChannel();
  CHECK(!build_channel.name.empty());

  return base::DictValue().Set(kBuildChannelKey, build_channel.name);
}

}  // namespace catsxp_ads
