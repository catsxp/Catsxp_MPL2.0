/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_SYNC_CATSXP_SYNC_ALERTS_SERVICE_FACTORY_H_
#define CATSXP_BROWSER_SYNC_CATSXP_SYNC_ALERTS_SERVICE_FACTORY_H_

#include <memory>

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

class CatsxpSyncAlertsService;

class CatsxpSyncAlertsServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  CatsxpSyncAlertsServiceFactory(const CatsxpSyncAlertsServiceFactory&) = delete;
  CatsxpSyncAlertsServiceFactory& operator=(
      const CatsxpSyncAlertsServiceFactory&) = delete;

  static CatsxpSyncAlertsService* GetForBrowserContext(
      content::BrowserContext* context);

  static CatsxpSyncAlertsServiceFactory* GetInstance();

 private:
  friend base::NoDestructor<CatsxpSyncAlertsServiceFactory>;

  CatsxpSyncAlertsServiceFactory();
  ~CatsxpSyncAlertsServiceFactory() override;

  // BrowserContextKeyedServiceFactory:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
  content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const override;
  bool ServiceIsCreatedWithBrowserContext() const override;
  bool ServiceIsNULLWhileTesting() const override;
};

#endif  // CATSXP_BROWSER_SYNC_CATSXP_SYNC_ALERTS_SERVICE_FACTORY_H_
