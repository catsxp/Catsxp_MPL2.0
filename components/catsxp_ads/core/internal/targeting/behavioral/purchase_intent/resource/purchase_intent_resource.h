/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_RESOURCE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_RESOURCE_H_

#include <optional>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_resource_info.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace catsxp_ads {

class AdsClient;

class PurchaseIntentResource final : public AdsClientNotifierObserver {
 public:
  PurchaseIntentResource();

  PurchaseIntentResource(const PurchaseIntentResource&) = delete;
  PurchaseIntentResource& operator=(const PurchaseIntentResource&) = delete;

  ~PurchaseIntentResource() override;

  bool IsLoaded() const { return !!resource_; }

  std::optional<std::string> GetManifestVersion() const {
    return manifest_version_;
  }

  const std::optional<PurchaseIntentResourceInfo>& get() const {
    return resource_;
  }

 private:
  void MaybeLoad();
  void MaybeLoadOrUnload();

  void Load();
  void LoadCallback(std::optional<PurchaseIntentResourceInfo> resource);

  void MaybeUnload();
  void Unload();

  // AdsClientNotifierObserver:
  void OnNotifyPrefDidChange(const std::string& path) override;
  void OnNotifyResourceComponentDidChange(const std::string& manifest_version,
                                          const std::string& id) override;
  void OnNotifyDidUnregisterResourceComponent(const std::string& id) override;

  std::optional<std::string> manifest_version_;

  std::optional<PurchaseIntentResourceInfo> resource_;

  base::ScopedObservation<AdsClient, AdsClientNotifierObserver>
      ads_client_observation_{this};

  base::WeakPtrFactory<PurchaseIntentResource> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_RESOURCE_H_
