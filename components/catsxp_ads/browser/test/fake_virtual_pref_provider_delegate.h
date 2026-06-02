/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_VIRTUAL_PREF_PROVIDER_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_VIRTUAL_PREF_PROVIDER_DELEGATE_H_

#include <string>
#include <string_view>

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/browser/virtual_pref/virtual_pref_provider.h"

namespace catsxp_ads::test {

// No-op implementation of `VirtualPrefProvider::Delegate` for unit tests.
class FakeVirtualPrefProviderDelegate : public VirtualPrefProvider::Delegate {
 public:
  FakeVirtualPrefProviderDelegate();

  FakeVirtualPrefProviderDelegate(const FakeVirtualPrefProviderDelegate&) =
      delete;
  FakeVirtualPrefProviderDelegate& operator=(
      const FakeVirtualPrefProviderDelegate&) = delete;

  ~FakeVirtualPrefProviderDelegate() override;

  // VirtualPrefProvider::Delegate:
  std::string_view GetChannel() const override;
  std::string GetDefaultSearchEngineName() const override;
  base::DictValue GetSerpMetrics() const override;
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_VIRTUAL_PREF_PROVIDER_DELEGATE_H_
