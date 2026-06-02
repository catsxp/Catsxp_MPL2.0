/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_rewards/user_rewards_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"

namespace catsxp_ads {

void UpdateIssuers(const IssuersInfo& issuers) {
  if (!HasIssuersChanged(issuers)) {
    return BLOG(1, "Issuers already up to date");
  }

  BLOG(1, "Updated issuers");
  SetIssuers(issuers);
}

}  // namespace catsxp_ads
