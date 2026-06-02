/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_FILTER_LIST_CATALOG_PROVIDER_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_FILTER_LIST_CATALOG_PROVIDER_H_

#include <string>

#include "base/functional/callback.h"
#include "base/observer_list.h"
#include "base/observer_list_types.h"
#include "catsxp/components/catsxp_component_updater/browser/dat_file_util.h"

namespace component_updater {
class ComponentUpdateService;
}  // namespace component_updater

namespace base {
class FilePath;
}

namespace catsxp_shields {

class AdBlockFilterListCatalogProvider {
 public:
  class Observer : public base::CheckedObserver {
   public:
    virtual void OnFilterListCatalogLoaded(const std::string& catalog_json) = 0;
  };

  explicit AdBlockFilterListCatalogProvider(
      component_updater::ComponentUpdateService* cus);
  ~AdBlockFilterListCatalogProvider();
  AdBlockFilterListCatalogProvider(const AdBlockFilterListCatalogProvider&) =
      delete;
  AdBlockFilterListCatalogProvider& operator=(
      const AdBlockFilterListCatalogProvider&) = delete;

  void LoadFilterListCatalog(
      base::OnceCallback<void(const std::string& catalog_json)>);

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

 private:
  void OnFilterListCatalogLoaded(const std::string& catalog_json);
  void OnComponentReady(const base::FilePath&);

  base::FilePath component_path_;

  base::ObserverList<Observer> observers_;

  base::WeakPtrFactory<AdBlockFilterListCatalogProvider> weak_factory_{this};
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_FILTER_LIST_CATALOG_PROVIDER_H_
