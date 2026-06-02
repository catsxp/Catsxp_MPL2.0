/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_NTP_BACKGROUND_VIEW_COUNTER_SERVICE_FACTORY_H_
#define CATSXP_BROWSER_NTP_BACKGROUND_VIEW_COUNTER_SERVICE_FACTORY_H_

#include <memory>

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class Profile;

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace content {
class BrowserContext;
}  // namespace content

namespace user_prefs {
class PrefRegistrySyncable;
}  // namespace user_prefs

namespace ntp_background_images {

class ViewCounterService;

class ViewCounterServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  ViewCounterServiceFactory(const ViewCounterServiceFactory&) = delete;
  ViewCounterServiceFactory& operator=(const ViewCounterServiceFactory&) =
      delete;

  static ViewCounterService* GetForProfile(Profile* profile);
  static ViewCounterServiceFactory* GetInstance();

 private:
  friend base::NoDestructor<ViewCounterServiceFactory>;

  ViewCounterServiceFactory();
  ~ViewCounterServiceFactory() override;

  // BrowserContextKeyedServiceFactory:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
  bool ServiceIsCreatedWithBrowserContext() const override;
  void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) override;
};

}  // namespace ntp_background_images

#endif  // CATSXP_BROWSER_NTP_BACKGROUND_VIEW_COUNTER_SERVICE_FACTORY_H_
