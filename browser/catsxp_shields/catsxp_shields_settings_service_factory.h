/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_SHIELDS_CATSXP_SHIELDS_SETTINGS_SERVICE_FACTORY_H_
#define CATSXP_BROWSER_CATSXP_SHIELDS_CATSXP_SHIELDS_SETTINGS_SERVICE_FACTORY_H_

#include <memory>

#include "base/no_destructor.h"
#include "chrome/browser/profiles/profile_keyed_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/browser_context.h"

class Profile;

namespace catsxp_shields {
class CatsxpShieldsSettingsService;
}

class CatsxpShieldsSettingsServiceFactory : public ProfileKeyedServiceFactory {
 public:
  static CatsxpShieldsSettingsServiceFactory* GetInstance();
  static catsxp_shields::CatsxpShieldsSettingsService* GetForProfile(
      Profile* profile);

 private:
  friend base::NoDestructor<CatsxpShieldsSettingsServiceFactory>;

  CatsxpShieldsSettingsServiceFactory();
  ~CatsxpShieldsSettingsServiceFactory() override;

  // ProfileKeyedServiceFactory overrides:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
};

#endif  // CATSXP_BROWSER_CATSXP_SHIELDS_CATSXP_SHIELDS_SETTINGS_SERVICE_FACTORY_H_
