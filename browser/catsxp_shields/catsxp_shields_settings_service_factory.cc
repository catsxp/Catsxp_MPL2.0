/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_shields/catsxp_shields_settings_service_factory.h"

#include "base/no_destructor.h"
#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_settings_service.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_selections.h"
#include "content/public/browser/browser_context.h"

// static
CatsxpShieldsSettingsServiceFactory*
CatsxpShieldsSettingsServiceFactory::GetInstance() {
  static base::NoDestructor<CatsxpShieldsSettingsServiceFactory> instance;
  return instance.get();
}

// static
catsxp_shields::CatsxpShieldsSettingsService*
CatsxpShieldsSettingsServiceFactory::GetForProfile(Profile* profile) {
  return static_cast<catsxp_shields::CatsxpShieldsSettingsService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

CatsxpShieldsSettingsServiceFactory::CatsxpShieldsSettingsServiceFactory()
    : ProfileKeyedServiceFactory(
          "CatsxpShieldsSettingsService",
          ProfileSelections::Builder()
              // this should match HostContentSettingsMapFactory
              .WithRegular(ProfileSelection::kOwnInstance)
              .WithGuest(ProfileSelection::kOwnInstance)
              .Build()) {
  DependsOn(HostContentSettingsMapFactory::GetInstance());
}

CatsxpShieldsSettingsServiceFactory::~CatsxpShieldsSettingsServiceFactory() =
    default;

std::unique_ptr<KeyedService>
CatsxpShieldsSettingsServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  auto* profile = Profile::FromBrowserContext(context);
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile);
  CHECK(map);
  return std::make_unique<catsxp_shields::CatsxpShieldsSettingsService>(
      *map, g_browser_process->local_state(), profile->GetPrefs());
}
