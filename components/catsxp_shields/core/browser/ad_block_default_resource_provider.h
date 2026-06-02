/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_DEFAULT_RESOURCE_PROVIDER_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_DEFAULT_RESOURCE_PROVIDER_H_

#include "base/functional/callback.h"
#include "catsxp/components/catsxp_shields/core/browser/ad_block_resource_provider.h"

namespace component_updater {
class ComponentUpdateService;
}  // namespace component_updater

namespace base {
class FilePath;
}

class AdBlockServiceTest;

namespace catsxp_shields {

class AdBlockDefaultResourceProvider : public AdBlockResourceProvider {
 public:
  explicit AdBlockDefaultResourceProvider(
      component_updater::ComponentUpdateService* cus);
  ~AdBlockDefaultResourceProvider() override;
  AdBlockDefaultResourceProvider(const AdBlockDefaultResourceProvider&) =
      delete;
  AdBlockDefaultResourceProvider& operator=(
      const AdBlockDefaultResourceProvider&) = delete;

  /// Returns the path to the resources file.
  base::FilePath GetResourcesPath();

  void LoadResources(
      base::OnceCallback<void(AdblockResourceStorageBox)>) override;

 private:
  friend class ::AdBlockServiceTest;

  void OnComponentReady(const base::FilePath&);

  base::FilePath component_path_;

  base::WeakPtrFactory<AdBlockDefaultResourceProvider> weak_factory_{this};
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_DEFAULT_RESOURCE_PROVIDER_H_
