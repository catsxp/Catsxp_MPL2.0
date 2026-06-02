/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_RESOURCE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_RESOURCE_H_

#include <memory>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_observer.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_url_request_delegate.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace catsxp_ads {

class AdsClient;
class CatalogUrlRequest;
class DatabaseManager;
struct CatalogInfo;

// Manages periodic fetching, storage, and distribution of the Catsxp Ads
// catalog component.
class CatalogResource final : public AdsClientNotifierObserver,
                              public CatalogUrlRequestDelegate,
                              public DatabaseManagerObserver {
 public:
  CatalogResource();

  CatalogResource(const CatalogResource&) = delete;
  CatalogResource& operator=(const CatalogResource&) = delete;

  ~CatalogResource() override;

  void AddObserver(CatalogObserver* observer);
  void RemoveObserver(CatalogObserver* observer);

 private:
  void Initialize();

  void MaybeRequireCatalog();
  void InitializeCatalogUrlRequest();
  void ShutdownCatalogUrlRequest();

  void MaybeFetchCatalog() const;

  void NotifyDidFetchCatalog(const CatalogInfo& catalog);
  void OnDidFetchCatalogCallback(const CatalogInfo& catalog, bool success);
  void NotifyFailedToFetchCatalog();

  // AdsClientNotifierObserver:
  void OnNotifyDidInitializeAds() override;
  void OnNotifyPrefDidChange(const std::string& path) override;

  // CatalogUrlRequestDelegate:
  void OnDidFetchCatalog(const CatalogInfo& catalog) override;
  void OnFailedToFetchCatalog() override;

  // DatabaseManagerObserver:
  void OnDidMigrateDatabase(int from_version, int to_version) override;

  base::ObserverList<CatalogObserver> observers_;

  std::unique_ptr<CatalogUrlRequest> catalog_url_request_;

  base::ScopedObservation<AdsClient, AdsClientNotifierObserver>
      ads_client_observation_{this};

  base::ScopedObservation<DatabaseManager, DatabaseManagerObserver>
      database_manager_observation_{this};

  base::WeakPtrFactory<CatalogResource> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_RESOURCE_H_
