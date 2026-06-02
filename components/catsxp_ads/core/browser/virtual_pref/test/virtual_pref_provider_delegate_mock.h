/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_VIRTUAL_PREF_TEST_VIRTUAL_PREF_PROVIDER_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_VIRTUAL_PREF_TEST_VIRTUAL_PREF_PROVIDER_DELEGATE_MOCK_H_

#include <string>
#include <string_view>

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/browser/virtual_pref/virtual_pref_provider.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

// Mock for VirtualPrefProvider::Delegate used in unit tests.
class VirtualPrefProviderDelegateMock : public VirtualPrefProvider::Delegate {
 public:
  VirtualPrefProviderDelegateMock();

  VirtualPrefProviderDelegateMock(const VirtualPrefProviderDelegateMock&) =
      delete;
  VirtualPrefProviderDelegateMock& operator=(
      const VirtualPrefProviderDelegateMock&) = delete;

  ~VirtualPrefProviderDelegateMock() override;

  MOCK_METHOD(std::string_view, GetChannel, (), (const, override));

  MOCK_METHOD(std::string, GetDefaultSearchEngineName, (), (const, override));

  MOCK_METHOD(base::DictValue, GetSerpMetrics, (), (const, override));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_VIRTUAL_PREF_TEST_VIRTUAL_PREF_PROVIDER_DELEGATE_MOCK_H_
