/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_BAT_ADS_SERVICE_FACTORY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_BAT_ADS_SERVICE_FACTORY_H_

#include "catsxp/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "mojo/public/cpp/bindings/remote.h"

namespace catsxp_ads {

class BatAdsServiceFactory {
 public:
  virtual ~BatAdsServiceFactory() = default;

  // Launches a new Bat Ads Service.
  virtual mojo::Remote<bat_ads::mojom::BatAdsService> Launch() const = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_BAT_ADS_SERVICE_FACTORY_H_
