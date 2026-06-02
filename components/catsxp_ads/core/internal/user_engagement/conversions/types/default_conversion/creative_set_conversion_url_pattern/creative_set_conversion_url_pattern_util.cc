/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/types/default_conversion/creative_set_conversion_url_pattern/creative_set_conversion_url_pattern_util.h"

#include "base/containers/span.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"
#include "catsxp/components/catsxp_ads/core/public/common/url/url_util.h"
#include "url/gurl.h"

namespace catsxp_ads {

bool DoesCreativeSetConversionUrlPatternMatchRedirectChain(
    const CreativeSetConversionInfo& creative_set_conversion,
    base::span<const GURL> redirect_chain) {
  return MatchUrlPattern(redirect_chain, creative_set_conversion.url_pattern);
}

}  // namespace catsxp_ads
