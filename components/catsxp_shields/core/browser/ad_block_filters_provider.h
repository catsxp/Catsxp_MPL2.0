/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_FILTERS_PROVIDER_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_FILTERS_PROVIDER_H_

#include <string>

#include "base/functional/callback.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/observer_list_types.h"
#include "catsxp/components/catsxp_component_updater/browser/dat_file_util.h"
#include "catsxp/components/catsxp_shields/core/common/adblock/rs/src/lib.rs.h"
#include "third_party/rust/cxx/v1/cxx.h"

using catsxp_component_updater::DATFileDataBuffer;

namespace catsxp_shields {

class AdBlockFiltersProviderManager;

// Interface for any source that can load filters or serialized filter data
// into an adblock engine.
class AdBlockFiltersProvider {
 public:
  class Observer : public base::CheckedObserver {
   public:
    virtual void OnChanged(bool is_for_default_engine) = 0;
  };

  explicit AdBlockFiltersProvider(
      bool engine_is_default,
      AdBlockFiltersProviderManager* filters_provider_manager_);
  // Used by AdblockFiltersProviderManager
  AdBlockFiltersProvider();
  AdBlockFiltersProvider(const AdBlockFiltersProvider&) = delete;
  AdBlockFiltersProvider& operator=(const AdBlockFiltersProvider&) = delete;
  virtual ~AdBlockFiltersProvider();

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  virtual void LoadFilterSet(
      base::OnceCallback<
          void(base::OnceCallback<void(rust::Box<adblock::FilterSet>*)>)>) = 0;

  base::WeakPtr<AdBlockFiltersProvider> AsWeakPtr();

  virtual std::string GetNameForDebugging() = 0;

  // Intended to be overridden if the provider implementation is not immediately
  // ready at creation time.
  virtual bool IsInitialized() const;

 protected:
  bool engine_is_default_;

  raw_ptr<AdBlockFiltersProviderManager> filters_provider_manager_;
  void NotifyObservers(bool is_for_default_engine);

 private:
  base::ObserverList<Observer> observers_;
  base::WeakPtrFactory<AdBlockFiltersProvider> weak_factory_{this};
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_FILTERS_PROVIDER_H_
