/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_VIRTUAL_PREF_PROVIDER_DELEGATE_H_
#define CATSXP_BROWSER_CATSXP_ADS_VIRTUAL_PREF_PROVIDER_DELEGATE_H_

#include <string>
#include <string_view>

#include "base/memory/raw_ref.h"
#include "catsxp/components/catsxp_ads/core/browser/virtual_pref/virtual_pref_provider.h"

class Profile;
class ProfileAttributesStorage;

namespace base {
class DictValue;
}  // namespace base

namespace catsxp_ads {

class VirtualPrefProviderDelegate final : public VirtualPrefProvider::Delegate {
 public:
  VirtualPrefProviderDelegate(
      Profile& profile,
      ProfileAttributesStorage& profile_attributes_storage);

  VirtualPrefProviderDelegate(const VirtualPrefProviderDelegate&) = delete;
  VirtualPrefProviderDelegate& operator=(const VirtualPrefProviderDelegate&) =
      delete;

  ~VirtualPrefProviderDelegate() override;

  // VirtualPrefProvider::Delegate:
  std::string_view GetChannel() const override;

  std::string GetDefaultSearchEngineName() const override;

  base::DictValue GetSerpMetrics() const override;

 private:
  const raw_ref<Profile> profile_;
  const raw_ref<ProfileAttributesStorage> profile_attributes_storage_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_VIRTUAL_PREF_PROVIDER_DELEGATE_H_
