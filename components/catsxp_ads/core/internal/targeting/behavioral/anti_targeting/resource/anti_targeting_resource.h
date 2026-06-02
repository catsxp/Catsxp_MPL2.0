/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_RESOURCE_ANTI_TARGETING_RESOURCE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_RESOURCE_ANTI_TARGETING_RESOURCE_H_

#include <optional>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/anti_targeting/resource/anti_targeting_resource_info.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace catsxp_ads {

class AdsClient;

class AntiTargetingResource final : public AdsClientNotifierObserver {
 public:
  AntiTargetingResource();

  AntiTargetingResource(const AntiTargetingResource&) = delete;
  AntiTargetingResource& operator=(const AntiTargetingResource&) = delete;

  ~AntiTargetingResource() override;

  bool IsLoaded() const { return !!resource_; }

  std::optional<std::string> GetManifestVersion() const {
    return manifest_version_;
  }

  AntiTargetingSiteList GetSites(const std::string& creative_set_id) const;

 private:
  void MaybeLoad();
  void MaybeLoadOrUnload();

  void Load();
  void LoadCallback(std::optional<AntiTargetingResourceInfo> resource);

  void MaybeUnload();
  void Unload();

  // AdsClientNotifierObserver:
  void OnNotifyPrefDidChange(const std::string& path) override;
  void OnNotifyResourceComponentDidChange(const std::string& manifest_version,
                                          const std::string& id) override;
  void OnNotifyDidUnregisterResourceComponent(const std::string& id) override;

  std::optional<std::string> manifest_version_;

  std::optional<AntiTargetingResourceInfo> resource_;

  base::ScopedObservation<AdsClient, AdsClientNotifierObserver>
      ads_client_observation_{this};

  base::WeakPtrFactory<AntiTargetingResource> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_RESOURCE_ANTI_TARGETING_RESOURCE_H_
