/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_H_

#include <map>
#include <optional>
#include <string>

#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "catsxp/components/catsxp_ads/browser/component_updater/resource_component_observer.h"
#include "catsxp/components/catsxp_ads/browser/component_updater/resource_component_registrar.h"
#include "catsxp/components/catsxp_ads/browser/component_updater/resource_component_registrar_delegate.h"
#include "catsxp/components/catsxp_ads/browser/component_updater/resource_info.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_component_updater/browser/catsxp_component.h"

namespace catsxp_ads {
class ResourceComponentObserver;
}  // namespace catsxp_ads

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

class ResourceComponent : public ResourceComponentRegistrarDelegate {
 public:
  explicit ResourceComponent(
      catsxp_component_updater::CatsxpComponent::Delegate* delegate);

  ResourceComponent(const ResourceComponent&) = delete;
  ResourceComponent& operator=(const ResourceComponent&) = delete;

  ~ResourceComponent() override;

  void AddObserver(ResourceComponentObserver* observer);
  void RemoveObserver(ResourceComponentObserver* observer);

  virtual void RegisterCountryComponent(const std::string& country_code);
  virtual void UnregisterCountryComponent();
  virtual void RegisterLanguageComponent(const std::string& language_code);
  virtual void UnregisterLanguageComponent();

  std::optional<base::FilePath> MaybeGetPath(const std::string& id,
                                             int version);

 private:
  void LoadManifestCallback(const std::string& component_id,
                            const base::FilePath& install_dir,
                            const std::string& json);

  void LoadResourceCallback(const std::string& manifest_version,
                            const std::string& component_id,
                            const base::FilePath& install_dir,
                            const std::string& json);

  void NotifyResourceComponentDidChange(const std::string& manifest_version,
                                        const std::string& id);
  void NotifyDidUnregisterResourceComponent(const std::string& id);

  // ResourceComponentRegistrarDelegate:
  void OnResourceComponentRegistered(
      const std::string& component_id,
      const base::FilePath& install_dir) override;
  void OnResourceComponentUnregistered(
      const std::string& component_id) override;

  base::ObserverList<ResourceComponentObserver> observers_;

  ResourceComponentRegistrar country_resource_component_registrar_;
  ResourceComponentRegistrar language_resource_component_registrar_;
  std::map</*resource_key*/ std::string, ResourceInfo> resources_;

  base::WeakPtrFactory<ResourceComponent> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_H_
