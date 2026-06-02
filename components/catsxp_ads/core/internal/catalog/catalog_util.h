/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_UTIL_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace base {
class Time;
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

struct CatalogInfo;

void SaveCatalog(const CatalogInfo& catalog, ResultCallback callback);
void ResetCatalog(ResultCallback callback);

std::string GetCatalogId();
void SetCatalogId(const std::string& id);

int GetCatalogVersion();
void SetCatalogVersion(int version);

base::TimeDelta GetCatalogPing();
void SetCatalogPing(base::TimeDelta ping);

base::Time GetCatalogLastUpdated();
void SetCatalogLastUpdated(base::Time last_updated_at);

bool DoesCatalogExist();
bool HasCatalogChanged(const std::string& catalog_id);
bool HasCatalogExpired();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_UTIL_H_
