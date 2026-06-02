/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_USER_MODEL_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_USER_MODEL_INFO_H_

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/intent/intent_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/interest/interest_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/latent_interest/latent_interest_user_model_info.h"

namespace catsxp_ads {

struct UserModelInfo final {
  UserModelInfo();
  UserModelInfo(IntentUserModelInfo intent,
                LatentInterestUserModelInfo latent_interest,
                InterestUserModelInfo interest);

  UserModelInfo(const UserModelInfo&);
  UserModelInfo& operator=(const UserModelInfo&);

  UserModelInfo(UserModelInfo&&) noexcept;
  UserModelInfo& operator=(UserModelInfo&&) noexcept;

  ~UserModelInfo();

  bool operator==(const UserModelInfo&) const = default;

  IntentUserModelInfo intent;
  LatentInterestUserModelInfo latent_interest;
  InterestUserModelInfo interest;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_USER_MODEL_INFO_H_
