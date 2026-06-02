/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/payload/confirmation_payload_json_writer.h"

#include <string_view>

#include "base/check.h"
#include "base/json/json_writer.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_type.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/payload/reward_confirmation_payload_util.h"

namespace catsxp_ads::json::writer {

namespace {

constexpr std::string_view kTransactionIdKey = "transactionId";
constexpr std::string_view kCreativeInstanceIdKey = "creativeInstanceId";
constexpr std::string_view kTypeKey = "type";

}  // namespace

std::string WriteConfirmationPayload(const ConfirmationInfo& confirmation) {
  auto dict =
      base::DictValue()
          .Set(kCreativeInstanceIdKey, confirmation.creative_instance_id)
          .Set(kTypeKey, ToString(confirmation.type));

  if (confirmation.reward) {
    dict.Set(kTransactionIdKey, confirmation.transaction_id);

    dict.Merge(BuildRewardConfirmationPayload(*confirmation.reward));
  }

  dict.Merge(confirmation.user_data.dynamic.Clone());

  dict.Merge(confirmation.user_data.fixed.Clone());

  std::string json;
  CHECK(base::JSONWriter::Write(dict, &json));
  return json;
}

}  // namespace catsxp_ads::json::writer
