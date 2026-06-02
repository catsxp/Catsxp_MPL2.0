/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DEPRECATED_CLIENT_CLIENT_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DEPRECATED_CLIENT_CLIENT_INFO_H_

#include <string>

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_signal_history_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/text_classification_types.h"

namespace catsxp_ads {

struct ClientInfo final {
  ClientInfo();

  ClientInfo(const ClientInfo&);
  ClientInfo& operator=(const ClientInfo&);

  ClientInfo(ClientInfo&&) noexcept;
  ClientInfo& operator=(ClientInfo&&) noexcept;

  ~ClientInfo();

  base::DictValue ToDict() const;
  [[nodiscard]] bool FromDict(const base::DictValue& dict);

  std::string ToJson() const;
  [[nodiscard]] bool FromJson(const std::string& json);

  TextClassificationProbabilityList text_classification_probabilities;
  PurchaseIntentSignalHistoryMap purchase_intent_signal_history;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DEPRECATED_CLIENT_CLIENT_INFO_H_
