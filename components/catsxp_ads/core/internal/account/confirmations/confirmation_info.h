/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATION_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATION_INFO_H_

#include <optional>
#include <string>
#include <vector>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/reward_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/user_data_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-shared.h"

namespace catsxp_ads {

struct ConfirmationInfo final {
  ConfirmationInfo();

  ConfirmationInfo(const ConfirmationInfo&);
  ConfirmationInfo& operator=(const ConfirmationInfo&);

  ConfirmationInfo(ConfirmationInfo&&) noexcept;
  ConfirmationInfo& operator=(ConfirmationInfo&&) noexcept;

  ~ConfirmationInfo();

  bool operator==(const ConfirmationInfo&) const = default;

  std::string transaction_id;
  std::string creative_instance_id;
  mojom::ConfirmationType type = mojom::ConfirmationType::kUndefined;
  mojom::AdType ad_type = mojom::AdType::kUndefined;
  std::optional<base::Time> created_at;
  std::optional<RewardInfo> reward;
  UserDataInfo user_data;
};

using ConfirmationList = std::vector<ConfirmationInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATION_INFO_H_
