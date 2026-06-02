/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_NTP_BACKGROUND_CATSXP_NTP_CUSTOM_BACKGROUND_SERVICE_FACTORY_H_
#define CATSXP_BROWSER_NTP_BACKGROUND_CATSXP_NTP_CUSTOM_BACKGROUND_SERVICE_FACTORY_H_

#include <memory>

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace ntp_background_images {
class CatsxpNTPCustomBackgroundService;
}  // namespace ntp_background_images

class CatsxpNTPCustomBackgroundServiceFactory
    : public BrowserContextKeyedServiceFactory {
 public:
  static ntp_background_images::CatsxpNTPCustomBackgroundService* GetForContext(
      content::BrowserContext* context);
  static CatsxpNTPCustomBackgroundServiceFactory* GetInstance();

 private:
  friend base::NoDestructor<CatsxpNTPCustomBackgroundServiceFactory>;

  CatsxpNTPCustomBackgroundServiceFactory();
  ~CatsxpNTPCustomBackgroundServiceFactory() override;

  CatsxpNTPCustomBackgroundServiceFactory(
      const CatsxpNTPCustomBackgroundServiceFactory&) = delete;
  CatsxpNTPCustomBackgroundServiceFactory& operator=(
      const CatsxpNTPCustomBackgroundServiceFactory&) = delete;

  // BrowserContextKeyedServiceFactory overrides:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
};

#endif  // CATSXP_BROWSER_NTP_BACKGROUND_CATSXP_NTP_CUSTOM_BACKGROUND_SERVICE_FACTORY_H_
