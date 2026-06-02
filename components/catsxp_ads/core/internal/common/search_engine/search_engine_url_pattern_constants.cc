/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/search_engine_url_pattern_constants.h"

#include "base/no_destructor.h"
#include "base/strings/strcat.h"
#include "base/strings/string_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/search_engine_domain_extension_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/search_engine_subdomain_constants.h"

namespace catsxp_ads {

const std::string& GetAmazonUrlPattern() {
  static const base::NoDestructor<std::string> kUrlPattern(base::StrCat(
      {"https://www.amazon.(",
       base::JoinString(kAmazonSearchEngineDomainExtensions, "|"), ")/"}));
  return *kUrlPattern;
}

const std::string& GetGoogleUrlPattern() {
  static const base::NoDestructor<std::string> kUrlPattern(base::StrCat(
      {"https://www.google.(",
       base::JoinString(kGoogleSearchEngineDomainExtensions, "|"), ")/"}));
  return *kUrlPattern;
}

const std::string& GetMojeekUrlPattern() {
  static const base::NoDestructor<std::string> kUrlPattern(base::StrCat(
      {"https://www.mojeek.(",
       base::JoinString(kMojeekSearchEngineDomainExtensions, "|"), ")/"}));
  return *kUrlPattern;
}

const std::string& GetWikipediaUrlPattern() {
  static const base::NoDestructor<std::string> kUrlPattern(base::StrCat(
      {"https://(", base::JoinString(kWikipediaSearchEngineSubdomains, "|"),
       ").wikipedia.org/"}));
  return *kUrlPattern;
}

const std::string& GetYahooUrlPattern() {
  static const base::NoDestructor<std::string> kUrlPattern(base::StrCat(
      {"https://((", base::JoinString(kYahooSearchEngineSubdomains, "|"),
       ").search.yahoo.com/|search.yahoo.com/)"}));
  return *kUrlPattern;
}

}  // namespace catsxp_ads
