/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_REGISTRAR_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_REGISTRAR_DELEGATE_H_

#include <string>

namespace base {
class FilePath;
}  // namespace base

namespace catsxp_ads {

class ResourceComponentRegistrarDelegate {
 public:
  // Invoked when a resource component is registered.
  virtual void OnResourceComponentRegistered(
      const std::string& component_id,
      const base::FilePath& install_dir) = 0;

  // Invoked when a resource component is unregistered.
  virtual void OnResourceComponentUnregistered(
      const std::string& component_id) = 0;

 protected:
  virtual ~ResourceComponentRegistrarDelegate() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_REGISTRAR_DELEGATE_H_
