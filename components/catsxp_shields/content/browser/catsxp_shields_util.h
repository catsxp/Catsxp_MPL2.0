/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_CATSXP_SHIELDS_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_CATSXP_SHIELDS_UTIL_H_

namespace content {
struct Referrer;
}

class GURL;
class HostContentSettingsMap;

namespace catsxp_shields {

// Referrers is always set along with cookies so there is no setter and
// these is just included for backwards compat.
bool AreReferrersAllowed(HostContentSettingsMap* map, const GURL& url);

bool IsSameOriginNavigation(const GURL& referrer, const GURL& target_url);

bool MaybeChangeReferrer(bool allow_referrers,
                         bool shields_up,
                         const GURL& current_referrer,
                         const GURL& target_url,
                         content::Referrer* output_referrer);

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_CATSXP_SHIELDS_UTIL_H_
