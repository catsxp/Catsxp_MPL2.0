/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/summary_user_data.h"

#include <string_view>
#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_type.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/summary_user_data_util.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/ad_type.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kSummaryKey = "totals";
constexpr std::string_view kAdFormatKey = "ad_format";

}  // namespace

base::DictValue BuildSummaryUserData(const PaymentTokenList& payment_tokens) {
  if (!UserHasJoinedCatsxpRewards()) {
    return {};
  }

  base::ListValue list;
  for (const auto& [mojom_ad_type, confirmations] :
       BuildAdTypeBuckets(payment_tokens)) {
    auto dict = base::DictValue().Set(kAdFormatKey, ToString(mojom_ad_type));

    for (const auto& [confirmation_type, count] : confirmations) {
      dict.Set(ToString(confirmation_type), count);
    }

    list.Append(std::move(dict));
  }

  return base::DictValue().Set(kSummaryKey, std::move(list));
}

}  // namespace catsxp_ads
