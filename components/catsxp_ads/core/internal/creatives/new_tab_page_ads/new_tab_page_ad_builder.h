/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_BUILDER_H_

#include <string>

namespace catsxp_ads {

struct CreativeNewTabPageAdInfo;
struct NewTabPageAdInfo;

NewTabPageAdInfo BuildNewTabPageAd(const CreativeNewTabPageAdInfo& creative_ad);

NewTabPageAdInfo BuildNewTabPageAd(const std::string& placement_id,
                                   const CreativeNewTabPageAdInfo& creative_ad);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_BUILDER_H_
