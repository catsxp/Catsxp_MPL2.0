/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_URL_UTIL_INTERNAL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_URL_UTIL_INTERNAL_H_

#include <string_view>

class GURL;

namespace catsxp_ads {

bool HasSearchQuery(const GURL& url);
bool ShouldSupportInternalUrl(const GURL& url);

bool HostHasRegistryControlledDomain(std::string_view host);

bool DoesETLDPlusOneContainWildcards(const GURL& url);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_URL_URL_UTIL_INTERNAL_H_
