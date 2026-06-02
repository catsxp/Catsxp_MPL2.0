/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/page_land_user_data.h"

#include <string_view>

#include "catsxp/components/catsxp_ads/core/internal/common/net/http/http_status_code_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kHttpResponseStatusKey = "httpResponseStatus";
constexpr char kNonsensicalHttpStatusCode[] = "---";

}  // namespace

base::DictValue BuildPageLandUserData(int http_status_code) {
  if (!UserHasJoinedCatsxpRewards()) {
    return {};
  }

  return base::DictValue().Set(kHttpResponseStatusKey,
                               HttpStatusCodeToString(http_status_code)
                                   .value_or(kNonsensicalHttpStatusCode));
}

}  // namespace catsxp_ads
