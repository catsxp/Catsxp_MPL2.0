/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_shields/filter_list_service_factory.h"

#include <memory>
#include <utility>

#include "base/no_destructor.h"
#include "catsxp/browser/catsxp_browser_process.h"
#include "catsxp/components/catsxp_shields/content/browser/filter_list_service.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"

namespace catsxp_shields {

// static
FilterListServiceFactory* FilterListServiceFactory::GetInstance() {
  static base::NoDestructor<FilterListServiceFactory> instance;
  return instance.get();
}

// static
mojo::PendingRemote<mojom::FilterListAndroidHandler>
FilterListServiceFactory::GetRemoteForProfile(Profile* profile) {
  auto* service = static_cast<FilterListService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));

  if (!service) {
    return mojo::PendingRemote<mojom::FilterListAndroidHandler>();
  }

  return service->MakeRemote();
}

// static
FilterListService* FilterListServiceFactory::GetServiceForContext(
    content::BrowserContext* context) {
  return static_cast<FilterListService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

// static
void FilterListServiceFactory::BindForContext(
    content::BrowserContext* context,
    mojo::PendingReceiver<mojom::FilterListAndroidHandler> receiver) {
  auto* filter_list_opt_in_service =
      FilterListServiceFactory::GetServiceForContext(context);
  if (filter_list_opt_in_service) {
    filter_list_opt_in_service->Bind(std::move(receiver));
  }
}

FilterListServiceFactory::FilterListServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "FilterListService",
          BrowserContextDependencyManager::GetInstance()) {}

FilterListServiceFactory::~FilterListServiceFactory() = default;

std::unique_ptr<KeyedService>
FilterListServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  return std::make_unique<FilterListService>(
      g_catsxp_browser_process->ad_block_service());
}

content::BrowserContext* FilterListServiceFactory::GetBrowserContextToUse(
    content::BrowserContext* context) const {
  return GetBrowserContextRedirectedInIncognito(context);
}

}  // namespace catsxp_shields
