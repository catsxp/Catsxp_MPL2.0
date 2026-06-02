/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_VIRTUAL_PREF_VIRTUAL_PREF_PROVIDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_VIRTUAL_PREF_VIRTUAL_PREF_PROVIDER_H_

#include <memory>
#include <string>
#include <string_view>

#include "base/memory/raw_ref.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

class PrefService;

namespace base {
class DictValue;
}  // namespace base

// Provides a stable set of virtual pref paths for condition matching, exposing
// values that have no registered pref at all, and decoupling ads from
// registered pref paths so that targeting continues to work correctly even if
// those paths change in a future browser version, all evaluated locally with
// nothing leaving the device.

namespace catsxp_ads {

class VirtualPrefProvider final {
 public:
  class Delegate {
   public:
    virtual ~Delegate() = default;

    virtual std::string_view GetChannel() const = 0;

    virtual std::string GetDefaultSearchEngineName() const = 0;

    virtual base::DictValue GetSerpMetrics() const = 0;
  };

  VirtualPrefProvider(PrefService& prefs,
                      PrefService& local_state,
                      std::unique_ptr<Delegate> delegate);

  VirtualPrefProvider(const VirtualPrefProvider&) = delete;
  VirtualPrefProvider& operator=(const VirtualPrefProvider&) = delete;

  ~VirtualPrefProvider();

  base::DictValue GetPrefs() const;

 private:
  const raw_ref<PrefService> prefs_;
  const raw_ref<PrefService> local_state_;

  const std::unique_ptr<Delegate> delegate_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_VIRTUAL_PREF_VIRTUAL_PREF_PROVIDER_H_
