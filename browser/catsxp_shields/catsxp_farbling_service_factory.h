/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_SHIELDS_CATSXP_FARBLING_SERVICE_FACTORY_H_
#define CATSXP_BROWSER_CATSXP_SHIELDS_CATSXP_FARBLING_SERVICE_FACTORY_H_

#include <memory>

#include "chrome/browser/profiles/profile_keyed_service_factory.h"

class Profile;
namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace catsxp {
class CatsxpFarblingService;

class CatsxpFarblingServiceFactory : public ProfileKeyedServiceFactory {
 public:
  CatsxpFarblingServiceFactory(const CatsxpFarblingServiceFactory&) = delete;
  CatsxpFarblingServiceFactory& operator=(const CatsxpFarblingServiceFactory&) =
      delete;

  static CatsxpFarblingServiceFactory* GetInstance();
  static CatsxpFarblingService* GetForProfile(Profile* profile);

 private:
  friend base::NoDestructor<CatsxpFarblingServiceFactory>;

  CatsxpFarblingServiceFactory();
  ~CatsxpFarblingServiceFactory() override;

  // ProfileKeyedServiceFactory overrides:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
};
}  // namespace catsxp

#endif  // CATSXP_BROWSER_CATSXP_SHIELDS_CATSXP_FARBLING_SERVICE_FACTORY_H_
