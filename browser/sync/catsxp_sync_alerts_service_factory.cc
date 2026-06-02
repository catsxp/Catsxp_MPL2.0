/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/sync/catsxp_sync_alerts_service_factory.h"

#include <memory>

#include "base/no_destructor.h"
#include "catsxp/browser/sync/catsxp_sync_alerts_service.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/sync/sync_service_factory.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/pref_registry/pref_registry_syncable.h"

// static
CatsxpSyncAlertsService* CatsxpSyncAlertsServiceFactory::GetForBrowserContext(
    content::BrowserContext* context) {
  return static_cast<CatsxpSyncAlertsService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

// static
CatsxpSyncAlertsServiceFactory* CatsxpSyncAlertsServiceFactory::GetInstance() {
  static base::NoDestructor<CatsxpSyncAlertsServiceFactory> instance;
  return instance.get();
}

CatsxpSyncAlertsServiceFactory::CatsxpSyncAlertsServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "CatsxpSyncAlertsService",
          BrowserContextDependencyManager::GetInstance()) {
  DependsOn(SyncServiceFactory::GetInstance());
}

CatsxpSyncAlertsServiceFactory::~CatsxpSyncAlertsServiceFactory() {}

std::unique_ptr<KeyedService>
CatsxpSyncAlertsServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  return std::make_unique<CatsxpSyncAlertsService>(
      Profile::FromBrowserContext(context));
}

content::BrowserContext* CatsxpSyncAlertsServiceFactory::GetBrowserContextToUse(
    content::BrowserContext* context) const {
  return GetBrowserContextRedirectedInIncognito(context);
}

bool CatsxpSyncAlertsServiceFactory::ServiceIsCreatedWithBrowserContext() const {
  return true;
}

bool CatsxpSyncAlertsServiceFactory::ServiceIsNULLWhileTesting() const {
  return true;
}
