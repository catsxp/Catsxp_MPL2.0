/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CONTAINERS_CONTAINERS_SERVICE_FACTORY_H_
#define CATSXP_BROWSER_CONTAINERS_CONTAINERS_SERVICE_FACTORY_H_

#include "base/no_destructor.h"
#include "chrome/browser/profiles/profile_keyed_service_factory.h"

class Profile;

namespace containers {
class ContainersService;
}

class ContainersServiceFactory : public ProfileKeyedServiceFactory {
 public:
  static ContainersServiceFactory* GetInstance();
  static containers::ContainersService* GetForProfile(Profile* profile);

 private:
  friend base::NoDestructor<ContainersServiceFactory>;

  void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry) final;
  bool ServiceIsCreatedWithBrowserContext() const override;

  ContainersServiceFactory();
  ~ContainersServiceFactory() override;

  ContainersServiceFactory(const ContainersServiceFactory&) = delete;
  ContainersServiceFactory& operator=(const ContainersServiceFactory&) = delete;

  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
};

#endif  // CATSXP_BROWSER_CONTAINERS_CONTAINERS_SERVICE_FACTORY_H_
