/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/search_engine_results_page_url_pattern_constants.h"

#include "base/no_destructor.h"
#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/search_engine_url_pattern_constants.h"

namespace catsxp_ads {

const std::string& GetAmazonResultsPageUrlPattern() {
  static const base::NoDestructor<std::string> kUrlPattern(
      GetAmazonUrlPattern() + "s");
  return *kUrlPattern;
}

const std::string& GetGoogleResultsPageUrlPattern() {
  static const base::NoDestructor<std::string> kUrlPattern(
      GetGoogleUrlPattern() + "search");
  return *kUrlPattern;
}

const std::string& GetMojeekResultsPageUrlPattern() {
  static const base::NoDestructor<std::string> kUrlPattern(
      GetMojeekUrlPattern() + "search");
  return *kUrlPattern;
}

const std::string& GetWikipediaResultsPageUrlPattern() {
  static const base::NoDestructor<std::string> kUrlPattern(
      GetWikipediaUrlPattern() + "wiki/(.*)");
  return *kUrlPattern;
}

const std::string& GetYahooResultsPageUrlPattern() {
  static const base::NoDestructor<std::string> kUrlPattern(
      GetYahooUrlPattern() + "search(.*)");
  return *kUrlPattern;
}

}  // namespace catsxp_ads
