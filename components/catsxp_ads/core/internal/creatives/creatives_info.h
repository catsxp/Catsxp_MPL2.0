/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVES_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVES_INFO_H_

#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"

namespace catsxp_ads {

struct CreativesInfo final {
  CreativesInfo();

  CreativesInfo(const CreativesInfo&);
  CreativesInfo& operator=(const CreativesInfo&);

  CreativesInfo(CreativesInfo&&) noexcept;
  CreativesInfo& operator=(CreativesInfo&&) noexcept;

  ~CreativesInfo();

  CreativeNewTabPageAdList new_tab_page_ads;
  CreativeNotificationAdList notification_ads;

  CreativeSetConversionList conversions;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVES_INFO_H_
