/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_USER_ENGAGEMENT_REACTIONS_REACTIONS_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_USER_ENGAGEMENT_REACTIONS_REACTIONS_UTIL_H_

#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

struct AdHistoryItemInfo;

mojom::ReactionInfoPtr CreateReaction(const AdHistoryItemInfo& ad_history_item);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_USER_ENGAGEMENT_REACTIONS_REACTIONS_UTIL_H_
