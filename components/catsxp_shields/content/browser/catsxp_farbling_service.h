/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_CATSXP_FARBLING_SERVICE_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_CATSXP_FARBLING_SERVICE_H_

#include "base/containers/span.h"
#include "base/memory/raw_ptr.h"
#include "components/keyed_service/core/keyed_service.h"
#include "third_party/abseil-cpp/absl/random/random.h"

class GURL;

class HostContentSettingsMap;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace catsxp {

using FarblingPRNG = absl::random_internal::randen_engine<uint64_t>;

class CatsxpFarblingService : public KeyedService {
 public:
  explicit CatsxpFarblingService(
      HostContentSettingsMap* host_content_settings_map);
  ~CatsxpFarblingService() override;

  bool MakePseudoRandomGeneratorForURL(
      const GURL& url,
      base::span<const uint8_t> additional_entropy,
      FarblingPRNG* prng);

  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

 private:
  const raw_ptr<HostContentSettingsMap> host_content_settings_map_;
};

}  // namespace catsxp

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_CATSXP_FARBLING_SERVICE_H_
