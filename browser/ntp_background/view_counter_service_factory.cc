/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/ntp_background/view_counter_service_factory.h"

#include <memory>

#include "base/no_destructor.h"
#include "catsxp/browser/catsxp_browser_process.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/ntp_background_images/browser/ntp_background_images_source.h"
#include "catsxp/components/ntp_background_images/browser/ntp_sponsored_image_source.h"
#include "catsxp/components/ntp_background_images/browser/ntp_sponsored_rich_media_source.h"
#include "catsxp/components/ntp_background_images/browser/view_counter_service.h"
#include "catsxp/components/ntp_background_images/buildflags/buildflags.h"
#include "catsxp/components/ntp_background_images/common/view_counter_pref_registry.h"
#include "catsxp/components/p3a/buildflags.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/url_data_source.h"

#if BUILDFLAG(ENABLE_CATSXP_ADS)
#include "catsxp/browser/catsxp_ads/ads_service_factory.h"
#include "catsxp/components/catsxp_ads/core/browser/service/ads_service.h"
#include "catsxp/components/catsxp_ads/core/public/ads_util.h"
#endif

#if BUILDFLAG(ENABLE_CUSTOM_BACKGROUND)
#include "catsxp/browser/ntp_background/catsxp_ntp_custom_background_service_factory.h"
#endif

namespace ntp_background_images {

// static
ViewCounterService* ViewCounterServiceFactory::GetForProfile(Profile* profile) {
  return static_cast<ViewCounterService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

// static
ViewCounterServiceFactory* ViewCounterServiceFactory::GetInstance() {
  static base::NoDestructor<ViewCounterServiceFactory> instance;
  return instance.get();
}

ViewCounterServiceFactory::ViewCounterServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "ViewCounterService",
          BrowserContextDependencyManager::GetInstance()) {
#if BUILDFLAG(ENABLE_CATSXP_ADS)
  DependsOn(catsxp_ads::AdsServiceFactory::GetInstance());
#endif  // BUILDFLAG(ENABLE_CATSXP_ADS)
#if BUILDFLAG(ENABLE_CUSTOM_BACKGROUND)
  DependsOn(CatsxpNTPCustomBackgroundServiceFactory::GetInstance());
#endif
}

ViewCounterServiceFactory::~ViewCounterServiceFactory() = default;

std::unique_ptr<KeyedService>
ViewCounterServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* browser_context) const {
  // Only NTP in normal profile uses sponsored services.
  if (!Profile::FromBrowserContext(browser_context)->IsRegularProfile()) {
    return nullptr;
  }

  if (auto* service =
          g_catsxp_browser_process->ntp_background_images_service()) {
    Profile* profile = Profile::FromBrowserContext(browser_context);
#if BUILDFLAG(ENABLE_CATSXP_ADS)
    catsxp_ads::AdsService* const ads_service =
        catsxp_ads::AdsServiceFactory::GetForProfile(profile);
    const bool is_supported_locale =
        ads_service && catsxp_ads::IsSupportedRegion();
#else
    catsxp_ads::AdsService* const ads_service = nullptr;
    const bool is_supported_locale = false;
#endif

    content::URLDataSource::Add(
        browser_context, std::make_unique<NTPBackgroundImagesSource>(service));
    content::URLDataSource::Add(
        browser_context, std::make_unique<NTPSponsoredImageSource>(service));
    content::URLDataSource::Add(
        browser_context,
        std::make_unique<NTPSponsoredRichMediaSource>(service));

    return std::make_unique<ViewCounterService>(
        HostContentSettingsMapFactory::GetForProfile(profile), service,
#if BUILDFLAG(ENABLE_CUSTOM_BACKGROUND)
        CatsxpNTPCustomBackgroundServiceFactory::GetForContext(profile),
#else
        nullptr,
#endif
        ads_service, profile->GetPrefs(), g_browser_process->local_state(),
        is_supported_locale);
  }

  return nullptr;
}

void ViewCounterServiceFactory::RegisterProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry) {
  ::ntp_background_images::RegisterProfilePrefs(registry);
}

bool ViewCounterServiceFactory::ServiceIsCreatedWithBrowserContext() const {
  return true;
}

}  // namespace ntp_background_images
