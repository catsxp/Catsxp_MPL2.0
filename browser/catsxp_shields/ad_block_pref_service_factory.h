/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_SHIELDS_AD_BLOCK_PREF_SERVICE_FACTORY_H_
#define CATSXP_BROWSER_CATSXP_SHIELDS_AD_BLOCK_PREF_SERVICE_FACTORY_H_

#include <memory>

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace catsxp_shields {

class AdBlockPrefService;

class AdBlockPrefServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  AdBlockPrefServiceFactory(const AdBlockPrefServiceFactory&) = delete;
  AdBlockPrefServiceFactory& operator=(const AdBlockPrefServiceFactory&) =
      delete;

  static AdBlockPrefService* GetForBrowserContext(
      content::BrowserContext* context);

  static AdBlockPrefServiceFactory* GetInstance();

 private:
  friend base::NoDestructor<AdBlockPrefServiceFactory>;

  AdBlockPrefServiceFactory();
  ~AdBlockPrefServiceFactory() override;

  // BrowserContextKeyedServiceFactory:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;

  // We use the same service in both normal and incognito modes.
  content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const override;

  bool ServiceIsCreatedWithBrowserContext() const override;
};

}  // namespace catsxp_shields

#endif  // CATSXP_BROWSER_CATSXP_SHIELDS_AD_BLOCK_PREF_SERVICE_FACTORY_H_
