/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_RESOURCE_PROVIDER_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_RESOURCE_PROVIDER_H_

#include "base/functional/callback.h"
#include "base/observer_list.h"
#include "base/observer_list_types.h"
#include "catsxp/components/catsxp_component_updater/browser/dat_file_util.h"
#include "catsxp/components/catsxp_shields/core/common/adblock/rs/src/lib.rs.h"

using catsxp_component_updater::DATFileDataBuffer;

namespace catsxp_shields {

// C++ type alias for rust CatsxpCoreResourceStorage.
using AdblockResourceStorageBox = rust::Box<adblock::CatsxpCoreResourceStorage>;

// Interface for any source that can load resource replacements into an adblock
// engine.
class AdBlockResourceProvider {
 public:
  class Observer : public base::CheckedObserver {
   public:
    virtual void OnResourcesLoaded(AdblockResourceStorageBox) = 0;
  };

  AdBlockResourceProvider();
  virtual ~AdBlockResourceProvider();

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  virtual void LoadResources(
      base::OnceCallback<void(AdblockResourceStorageBox)>) = 0;

 protected:
  void NotifyResourcesLoaded(AdblockResourceStorageBox);

 private:
  base::ObserverList<Observer> observers_;
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_RESOURCE_PROVIDER_H_
