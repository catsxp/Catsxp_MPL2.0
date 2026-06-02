/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_COMMON_URL_URL_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_COMMON_URL_URL_UTIL_H_

#include <string>

#include "base/containers/span.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "url/gurl.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

GURL GetUrlExcludingQuery(const GURL& url);

// Returns `true` if the `url` is valid, does not have a port, username, or
// password, is not an IP address, the eTLD+1 does not contain an asterisk
// wildcard, and the host is either on the public suffix list or is a supported
// internal URL.
bool ShouldSupportUrl(const GURL& url);

// Returns `true` if the `url` matches the `pattern`. The pattern string can
// contain asterix wildcards. The backslash character (\) is an escape character
// for *. * matches 0 or more characters.
bool MatchUrlPattern(const GURL& url, const std::string& pattern);
bool MatchUrlPattern(base::span<const GURL> redirect_chain,
                     const std::string& pattern);

bool SameDomainOrHost(const GURL&, const GURL&);
bool DomainOrHostExists(base::span<const GURL> redirect_chain, const GURL& url);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_COMMON_URL_URL_UTIL_H_
