/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_SHIELDS_FILTER_LIST_SERVICE_FACTORY_H_
#define CATSXP_BROWSER_CATSXP_SHIELDS_FILTER_LIST_SERVICE_FACTORY_H_

#include <memory>

#include "catsxp/components/catsxp_shields/core/common/filter_list.mojom.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/browser_context.h"
#include "mojo/public/cpp/bindings/pending_remote.h"

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base
class Profile;

namespace catsxp_shields {

class FilterListService;

class FilterListServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  FilterListServiceFactory(const FilterListServiceFactory&) = delete;
  FilterListServiceFactory& operator=(const FilterListServiceFactory&) = delete;

  static mojo::PendingRemote<mojom::FilterListAndroidHandler>
  GetRemoteForProfile(Profile* profile);
  static FilterListService* GetServiceForContext(
      content::BrowserContext* context);
  static FilterListServiceFactory* GetInstance();
  static void BindForContext(
      content::BrowserContext* context,
      mojo::PendingReceiver<mojom::FilterListAndroidHandler> receiver);

 private:
  friend base::NoDestructor<FilterListServiceFactory>;

  FilterListServiceFactory();
  ~FilterListServiceFactory() override;

  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
  content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const override;
};

}  // namespace catsxp_shields

#endif  // CATSXP_BROWSER_CATSXP_SHIELDS_FILTER_LIST_SERVICE_FACTORY_H_
