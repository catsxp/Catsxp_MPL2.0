/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_REGISTRAR_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_REGISTRAR_H_

#include <optional>
#include <string>

#include "base/files/file_path.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/raw_ref.h"
#include "catsxp/components/catsxp_component_updater/browser/catsxp_component.h"

namespace catsxp_ads {

class ResourceComponentRegistrarDelegate;

class ResourceComponentRegistrar final
    : public catsxp_component_updater::CatsxpComponent {
 public:
  ResourceComponentRegistrar(Delegate* component_updater_delegate,
                             ResourceComponentRegistrarDelegate&
                                 resource_component_registrar_delegate);

  ResourceComponentRegistrar(const ResourceComponentRegistrar&) = delete;
  ResourceComponentRegistrar& operator=(const ResourceComponentRegistrar&) =
      delete;

  ~ResourceComponentRegistrar() override;

  void RegisterResourceComponent(const std::string& resource_id);
  void UnregisterResourceComponent();

 private:
  // catsxp_component_updater::CatsxpComponent:
  void OnComponentReady(const std::string& component_id,
                        const base::FilePath& install_dir,
                        const std::string& manifest) override;

  void OnComponentUnregistered(const std::string& component_id);

  const raw_ref<ResourceComponentRegistrarDelegate>
      resource_component_registrar_delegate_;
  std::optional<std::string> resource_component_id_;
  std::optional<base::FilePath> last_install_dir_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_REGISTRAR_H_
