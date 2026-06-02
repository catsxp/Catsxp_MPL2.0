/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_SERVICES_BAT_ADS_SERVICE_FACTORY_IMPL_H_
#define CATSXP_BROWSER_CATSXP_ADS_SERVICES_BAT_ADS_SERVICE_FACTORY_IMPL_H_

#include "catsxp/components/catsxp_ads/browser/bat_ads_service_factory.h"
#include "catsxp/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "mojo/public/cpp/bindings/remote.h"

namespace catsxp_ads {

class BatAdsServiceFactoryImpl final : public BatAdsServiceFactory {
 public:
  BatAdsServiceFactoryImpl();

  BatAdsServiceFactoryImpl(const BatAdsServiceFactoryImpl&) = delete;
  BatAdsServiceFactoryImpl& operator=(const BatAdsServiceFactoryImpl&) = delete;

  ~BatAdsServiceFactoryImpl() override;

  // BatAdsServiceFactory:
  mojo::Remote<bat_ads::mojom::BatAdsService> Launch() const override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_SERVICES_BAT_ADS_SERVICE_FACTORY_IMPL_H_
