/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENTS_H_

#include <string>

#include "base/containers/span.h"
#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

using AdEventCallback = base::OnceCallback<void(bool success)>;

struct AdEventInfo;
struct AdInfo;

void RecordAdEvent(const AdInfo& ad,
                   mojom::ConfirmationType mojom_confirmation_type,
                   AdEventCallback callback);
void RecordAdEvent(const AdEventInfo& ad_event, AdEventCallback callback);

void PurgeOrphanedAdEvents(mojom::AdType mojom_ad_type,
                           AdEventCallback callback);
void PurgeOrphanedAdEvents(base::span<const std::string> placement_ids,
                           AdEventCallback callback);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENTS_H_
