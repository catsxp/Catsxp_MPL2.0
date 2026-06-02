/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/user_model_info.h"

#include <utility>

namespace catsxp_ads {

UserModelInfo::UserModelInfo() = default;

UserModelInfo::UserModelInfo(IntentUserModelInfo intent,
                             LatentInterestUserModelInfo latent_interest,
                             InterestUserModelInfo interest)
    : intent(std::move(intent)),
      latent_interest(std::move(latent_interest)),
      interest(std::move(interest)) {}

UserModelInfo::UserModelInfo(const UserModelInfo& other) = default;

UserModelInfo& UserModelInfo::operator=(const UserModelInfo& other) = default;

UserModelInfo::UserModelInfo(UserModelInfo&& other) noexcept = default;

UserModelInfo& UserModelInfo::operator=(UserModelInfo&& other) noexcept =
    default;

UserModelInfo::~UserModelInfo() = default;

}  // namespace catsxp_ads
