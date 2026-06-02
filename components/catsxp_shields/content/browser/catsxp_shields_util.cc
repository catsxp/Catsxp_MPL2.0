/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/content/browser/catsxp_shields_util.h"

#include <utility>

#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings.h"
#include "content/public/common/referrer.h"
#include "url/gurl.h"
#include "url/origin.h"

#if !DCHECK_IS_ON()
#include "base/debug/dump_without_crashing.h"
#endif

using content::Referrer;

namespace catsxp_shields {

bool AreReferrersAllowed(HostContentSettingsMap* map, const GURL& url) {
  const ContentSetting setting =
      map->GetContentSetting(url, GURL(), ContentSettingsType::CATSXP_REFERRERS);

  return setting == CONTENT_SETTING_ALLOW;
}

bool IsSameOriginNavigation(const GURL& referrer, const GURL& target_url) {
  const url::Origin original_referrer = url::Origin::Create(referrer);
  const url::Origin target_origin = url::Origin::Create(target_url);

  return original_referrer.IsSameOriginWith(target_origin);
}

bool MaybeChangeReferrer(bool allow_referrers,
                         bool shields_up,
                         const GURL& current_referrer,
                         const GURL& target_url,
                         Referrer* output_referrer) {
  DCHECK(output_referrer);
  if (allow_referrers || !shields_up || current_referrer.is_empty()) {
    return false;
  }

  if (IsSameOriginNavigation(current_referrer, target_url)) {
    // Do nothing for same-origin requests. This check also prevents us from
    // sending referrer from HTTPS to HTTP.
    return false;
  }

  // Cap the referrer to "strict-origin-when-cross-origin". More restrictive
  // policies should be already applied.
  // See https://github.com/catsxp/catsxp-browser/issues/13464
  url::Origin current_referrer_origin = url::Origin::Create(current_referrer);
  *output_referrer = Referrer::SanitizeForRequest(
      target_url,
      Referrer(current_referrer_origin.GetURL(),
               network::mojom::ReferrerPolicy::kStrictOriginWhenCrossOrigin));

  return true;
}

}  // namespace catsxp_shields
