/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_CALLBACK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_CALLBACK_H_

#include <optional>

#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

using GetAdHistoryCallback =
    base::OnceCallback<void(std::optional<AdHistoryList> ad_history)>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_CALLBACK_H_
