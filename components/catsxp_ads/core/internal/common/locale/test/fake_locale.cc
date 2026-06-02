/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/locale/test/fake_locale.h"

namespace catsxp_ads::test {

FakeLocale::FakeLocale() {
  Locale::SetForTesting(this);
}

FakeLocale::~FakeLocale() {
  Locale::SetForTesting(nullptr);
}

void FakeLocale::SetLanguageCode(const std::string& language_code) {
  language_code_ = language_code;
}

void FakeLocale::SetCountryCode(const std::string& country_code) {
  country_code_ = country_code;
}

std::string FakeLocale::GetLanguageCode() const {
  return language_code_;
}

std::string FakeLocale::GetCountryCode() const {
  return country_code_;
}

}  // namespace catsxp_ads::test
