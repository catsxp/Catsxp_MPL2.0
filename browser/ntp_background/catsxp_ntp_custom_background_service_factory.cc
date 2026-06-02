/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/ntp_background/catsxp_ntp_custom_background_service_factory.h"

#include <memory>

#include "base/no_destructor.h"
#include "catsxp/browser/ntp_background/catsxp_ntp_custom_background_service_delegate.h"
#include "catsxp/components/ntp_background_images/browser/catsxp_ntp_custom_background_service.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"

// static
ntp_background_images::CatsxpNTPCustomBackgroundService*
CatsxpNTPCustomBackgroundServiceFactory::GetForContext(
    content::BrowserContext* context) {
  return static_cast<ntp_background_images::CatsxpNTPCustomBackgroundService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

// static
CatsxpNTPCustomBackgroundServiceFactory*
CatsxpNTPCustomBackgroundServiceFactory::GetInstance() {
  static base::NoDestructor<CatsxpNTPCustomBackgroundServiceFactory> instance;
  return instance.get();
}

CatsxpNTPCustomBackgroundServiceFactory::CatsxpNTPCustomBackgroundServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "CatsxpNTPCustomBackgroundService",
          BrowserContextDependencyManager::GetInstance()) {}

CatsxpNTPCustomBackgroundServiceFactory::
    ~CatsxpNTPCustomBackgroundServiceFactory() = default;

std::unique_ptr<KeyedService>
CatsxpNTPCustomBackgroundServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  // Custom NTP background is only used in normal profile.
  if (!Profile::FromBrowserContext(context)->IsRegularProfile()) {
    return nullptr;
  }

  return std::make_unique<
      ntp_background_images::CatsxpNTPCustomBackgroundService>(
      std::make_unique<CatsxpNTPCustomBackgroundServiceDelegate>(
          Profile::FromBrowserContext(context)));
}
