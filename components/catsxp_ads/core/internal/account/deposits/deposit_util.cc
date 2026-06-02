/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposit_util.h"

#include <string_view>
#include <utility>

#include "base/functional/bind.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_core/ads_core_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events_database_table.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kFirstTimeKey = "firstTime";

void CheckIfFirstTimeAndDepositWithUserDataCallback(
    mojom::AdType ad_type,
    mojom::ConfirmationType confirmation_type,
    const std::string& creative_instance_id,
    const std::string& segment,
    base::DictValue user_data,
    bool success,
    bool is_first_time) {
  if (!success) {
    return BLOG(0, "Failed to deposit");
  }

  if (is_first_time) {
    user_data.Set(kFirstTimeKey, true);
  }

  GetAccount().DepositWithUserData(creative_instance_id, segment, ad_type,
                                   confirmation_type, std::move(user_data));
}

void CheckIfFirstTimeAndDepositWithUserData(
    mojom::AdType ad_type,
    mojom::ConfirmationType confirmation_type,
    const std::string& campaign_id,
    const std::string& creative_instance_id,
    const std::string& segment,
    base::DictValue user_data) {
  database::table::AdEvents ad_events_database_table;
  ad_events_database_table.IsFirstTime(
      campaign_id, confirmation_type,
      base::BindOnce(&CheckIfFirstTimeAndDepositWithUserDataCallback, ad_type,
                     confirmation_type, creative_instance_id, segment,
                     std::move(user_data)));
}

}  // namespace

void DepositWithUserData(mojom::AdType ad_type,
                         mojom::ConfirmationType confirmation_type,
                         const std::string& campaign_id,
                         const std::string& creative_instance_id,
                         const std::string& segment,
                         base::DictValue user_data) {
  if (confirmation_type != mojom::ConfirmationType::kViewedImpression) {
    return GetAccount().DepositWithUserData(creative_instance_id, segment,
                                            ad_type, confirmation_type,
                                            std::move(user_data));
  }

  CheckIfFirstTimeAndDepositWithUserData(ad_type, confirmation_type,
                                         campaign_id, creative_instance_id,
                                         segment, std::move(user_data));
}

void Deposit(mojom::AdType ad_type,
             mojom::ConfirmationType confirmation_type,
             const std::string& campaign_id,
             const std::string& creative_instance_id,
             const std::string& segment) {
  DepositWithUserData(ad_type, confirmation_type, campaign_id,
                      creative_instance_id, segment,
                      /*user_data=*/base::DictValue());
}

}  // namespace catsxp_ads
