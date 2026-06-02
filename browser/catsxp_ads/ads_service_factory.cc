/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/ads_service_factory.h"

#include <cstddef>
#include <memory>

#include "base/check.h"
#include "base/functional/bind.h"
#include "base/no_destructor.h"
#include "catsxp/browser/catsxp_ads/ads_service_delegate.h"
#include "catsxp/browser/catsxp_ads/device_id/device_id_impl.h"
#include "catsxp/browser/catsxp_ads/services/bat_ads_service_factory_impl.h"
#include "catsxp/browser/catsxp_ads/tooltips/ads_tooltips_delegate_impl.h"
#include "catsxp/browser/catsxp_ads/virtual_pref_provider_delegate.h"
#include "catsxp/browser/catsxp_browser_process.h"
#include "catsxp/common/catsxp_channel_info.h"
#include "catsxp/components/catsxp_ads/browser/ads_service_impl.h"
#include "catsxp/components/catsxp_ads/core/browser/service/ads_service.h"
#include "catsxp/components/catsxp_ads/core/public/ads_util.h"
#include "catsxp/components/catsxp_policy/policy_initialization_waiter.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/history/history_service_factory.h"
#include "chrome/browser/notifications/notification_display_service.h"
#include "chrome/browser/notifications/notification_display_service_factory.h"
#include "chrome/browser/policy/profile_policy_connector.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/policy/core/common/policy_service.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/storage_partition.h"
#include "services/network/public/cpp/network_context_getter.h"

#if BUILDFLAG(ENABLE_CATSXP_REWARDS)
#include "catsxp/browser/catsxp_rewards/rewards_service_factory.h"
#include "catsxp/components/catsxp_adaptive_captcha/catsxp_adaptive_captcha_service.h"
#endif

namespace catsxp_ads {

namespace {

network::mojom::NetworkContext* GetNetworkContextForProfile(
    content::BrowserContext* context) {
  // Retrieves the `NetworkContext` from the default storage partition on
  // demand. A cached raw pointer will become invalid if the network service
  // crashes or restarts, so callers must not persist the returned pointer
  // beyond the current task.
  return context->GetDefaultStoragePartition()->GetNetworkContext();
}

}  // namespace

// static
AdsService* AdsServiceFactory::GetForProfile(Profile* profile) {
  if (!profile->IsRegularProfile()) {
    return nullptr;
  }

  return static_cast<AdsService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

// static
AdsServiceFactory* AdsServiceFactory::GetInstance() {
  static base::NoDestructor<AdsServiceFactory> instance;
  return instance.get();
}

AdsServiceFactory::AdsServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "AdsService",
          BrowserContextDependencyManager::GetInstance()) {
  DependsOn(NotificationDisplayServiceFactory::GetInstance());
#if BUILDFLAG(ENABLE_CATSXP_REWARDS)
  DependsOn(catsxp_rewards::RewardsServiceFactory::GetInstance());
  DependsOn(catsxp_adaptive_captcha::CatsxpAdaptiveCaptchaServiceFactory::
                GetInstance());
#endif
  DependsOn(HistoryServiceFactory::GetInstance());
  DependsOn(HostContentSettingsMapFactory::GetInstance());
}

AdsServiceFactory::~AdsServiceFactory() = default;

std::unique_ptr<AdsTooltipsDelegateImpl>
AdsServiceFactory::CreateAdsTooltipsDelegate() const {
#if BUILDFLAG(IS_ANDROID)
  return nullptr;
#else
  return std::make_unique<AdsTooltipsDelegateImpl>();
#endif
}

std::unique_ptr<KeyedService>
AdsServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  auto* profile = Profile::FromBrowserContext(context);

  auto* prefs = profile->GetPrefs();
  auto* local_state = g_browser_process->local_state();

  auto* default_store_partition = profile->GetDefaultStoragePartition();

  policy::PolicyService* policy_service = nullptr;
  if (auto* policy_connector = profile->GetProfilePolicyConnector()) {
    policy_service = policy_connector->policy_service();
  }
  auto policy_initialization_waiter =
      std::make_unique<catsxp_policy::PolicyInitializationWaiter>(
          policy_service);

  auto delegate = std::make_unique<AdsServiceDelegate>(
      *profile, *local_state
#if BUILDFLAG(ENABLE_CATSXP_REWARDS)
      ,
      catsxp_adaptive_captcha::CatsxpAdaptiveCaptchaServiceFactory::
          GetForProfile(profile)
#endif
  );

  auto* history_service = HistoryServiceFactory::GetForProfile(
      profile, ServiceAccessType::EXPLICIT_ACCESS);

#if BUILDFLAG(ENABLE_CATSXP_REWARDS)
  auto* rewards_service =
      catsxp_rewards::RewardsServiceFactory::GetForProfile(profile);
#endif  // BUILDFLAG(ENABLE_CATSXP_REWARDS)

  auto* host_content_settings_map =
      HostContentSettingsMapFactory::GetForProfile(profile);

  auto http_client = std::make_unique<HttpClient>(
      *local_state,
      default_store_partition->GetURLLoaderFactoryForBrowserProcess(),
      base::BindRepeating(&GetNetworkContextForProfile, context),
      /*use_ohttp_staging=*/IsStagingEnvironment(*prefs));

  ProfileManager* const profile_manager = g_browser_process->profile_manager();
  CHECK(profile_manager);

  return std::make_unique<AdsServiceImpl>(
      std::move(delegate), *prefs, *local_state,
      std::move(policy_initialization_waiter), std::move(http_client),
      std::make_unique<VirtualPrefProviderDelegate>(
          *profile, profile_manager->GetProfileAttributesStorage()),
      catsxp::GetChannelName(), profile->GetPath(), CreateAdsTooltipsDelegate(),
      std::make_unique<DeviceIdImpl>(),
      std::make_unique<BatAdsServiceFactoryImpl>(),
      g_catsxp_browser_process->resource_component(), history_service,
#if BUILDFLAG(ENABLE_CATSXP_REWARDS)
      rewards_service,
#endif
      host_content_settings_map);
}

bool AdsServiceFactory::ServiceIsNULLWhileTesting() const {
  return true;
}

}  // namespace catsxp_ads
