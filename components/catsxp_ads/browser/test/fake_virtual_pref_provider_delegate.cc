/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/test/fake_virtual_pref_provider_delegate.h"

#include "base/values.h"

namespace catsxp_ads::test {

FakeVirtualPrefProviderDelegate::FakeVirtualPrefProviderDelegate() = default;

FakeVirtualPrefProviderDelegate::~FakeVirtualPrefProviderDelegate() = default;

std::string_view FakeVirtualPrefProviderDelegate::GetChannel() const {
  return "";
}

std::string FakeVirtualPrefProviderDelegate::GetDefaultSearchEngineName()
    const {
  return "";
}

base::DictValue FakeVirtualPrefProviderDelegate::GetSerpMetrics() const {
  return {};
}

}  // namespace catsxp_ads::test
