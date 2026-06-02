/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_ADS_SERVICE_FACTORY_H_
#define CATSXP_BROWSER_CATSXP_ADS_ADS_SERVICE_FACTORY_H_

#include <memory>

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class Profile;

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace catsxp_ads {

class AdsService;
class AdsTooltipsDelegateImpl;

// Singleton that owns all AdsService and associates them with Profiles.
class AdsServiceFactory final : public BrowserContextKeyedServiceFactory {
 public:
  AdsServiceFactory(const AdsServiceFactory&) = delete;
  AdsServiceFactory& operator=(const AdsServiceFactory&) = delete;

  static AdsService* GetForProfile(Profile* profile);

  static AdsServiceFactory* GetInstance();

 private:
  friend base::NoDestructor<AdsServiceFactory>;

  AdsServiceFactory();

  ~AdsServiceFactory() override;

  std::unique_ptr<AdsTooltipsDelegateImpl> CreateAdsTooltipsDelegate() const;

  // BrowserContextKeyedServiceFactory:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
  bool ServiceIsNULLWhileTesting() const override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_ADS_SERVICE_FACTORY_H_
