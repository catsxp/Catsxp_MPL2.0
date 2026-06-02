/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_OBSERVER_H_

#include <string>

#include "base/observer_list_types.h"

namespace catsxp_ads {

class ResourceComponentObserver : public base::CheckedObserver {
 public:
  // Invoked when the resource for the given `id` has updated to
  // `manifest_version`.
  virtual void OnResourceComponentDidChange(const std::string& manifest_version,
                                            const std::string& id) = 0;

  // Invoked when the resource for the given `id` has been unregistered.
  virtual void OnDidUnregisterResourceComponent(const std::string& id) = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_OBSERVER_H_
