/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversion/conversion_builder.h"

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/actions/conversion_action_types_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversion/conversion_info.h"

namespace catsxp_ads {

ConversionInfo BuildConversion(const AdEventInfo& ad_event) {
  ConversionInfo conversion;

  conversion.ad_type = ad_event.type;
  conversion.creative_instance_id = ad_event.creative_instance_id;
  conversion.creative_set_id = ad_event.creative_set_id;
  conversion.campaign_id = ad_event.campaign_id;
  conversion.advertiser_id = ad_event.advertiser_id;
  conversion.segment = ad_event.segment;
  conversion.action_type = ToConversionActionType(ad_event.confirmation_type);

  return conversion;
}

}  // namespace catsxp_ads
