/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DEPRECATED_CLIENT_CLIENT_STATE_MANAGER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DEPRECATED_CLIENT_CLIENT_STATE_MANAGER_H_

#include <optional>
#include <string>

#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/deprecated/client/client_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_signal_history_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/text_classification_types.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads {

class ClientStateManager final {
 public:
  ClientStateManager();

  ClientStateManager(const ClientStateManager&) = delete;
  ClientStateManager& operator=(const ClientStateManager&) = delete;

  ~ClientStateManager();

  static ClientStateManager& GetInstance();

  bool IsInitialized() const { return is_initialized_; }

  void LoadState(ResultCallback callback);

  void AppendToPurchaseIntentSignalHistoryForSegment(
      const std::string& segment,
      const PurchaseIntentSignalHistoryInfo& history);
  const PurchaseIntentSignalHistoryMap& GetPurchaseIntentSignalHistory() const;

  void AppendTextClassificationProbabilitiesToHistory(
      const TextClassificationProbabilityMap& probabilities);
  const TextClassificationProbabilityList&
  GetTextClassificationProbabilitiesHistory() const;

 private:
  void SaveState();

  void LoadCallback(ResultCallback callback,
                    const std::optional<std::string>& json);

  [[nodiscard]] bool FromJson(const std::string& json);

  ClientInfo client_;

  bool is_initialized_ = false;

  base::WeakPtrFactory<ClientStateManager> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DEPRECATED_CLIENT_CLIENT_STATE_MANAGER_H_
