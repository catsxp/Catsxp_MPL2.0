/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_shields/catsxp_farbling_service_factory.h"

#include "base/no_destructor.h"
#include "catsxp/components/catsxp_shields/content/browser/catsxp_farbling_service.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/browser_context.h"

namespace catsxp {

// static
CatsxpFarblingServiceFactory* CatsxpFarblingServiceFactory::GetInstance() {
  static base::NoDestructor<CatsxpFarblingServiceFactory> instance;
  return instance.get();
}

// static
CatsxpFarblingService* CatsxpFarblingServiceFactory::GetForProfile(
    Profile* profile) {
  return static_cast<CatsxpFarblingService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

CatsxpFarblingServiceFactory::CatsxpFarblingServiceFactory()
    : ProfileKeyedServiceFactory(
          "CatsxpFarblingService",
          ProfileSelections::Builder()
              .WithRegular(ProfileSelection::kOwnInstance)
              .WithGuest(ProfileSelection::kOwnInstance)
              .WithSystem(ProfileSelection::kNone)
              .Build()) {
  DependsOn(HostContentSettingsMapFactory::GetInstance());
}

CatsxpFarblingServiceFactory::~CatsxpFarblingServiceFactory() = default;

std::unique_ptr<KeyedService>
CatsxpFarblingServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  return std::make_unique<CatsxpFarblingService>(
      HostContentSettingsMapFactory::GetForProfile(context));
}

}  // namespace catsxp
