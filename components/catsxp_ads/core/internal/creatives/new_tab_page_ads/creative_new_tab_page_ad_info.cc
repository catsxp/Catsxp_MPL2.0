/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_info.h"

namespace catsxp_ads {

CreativeNewTabPageAdInfo::CreativeNewTabPageAdInfo() = default;

CreativeNewTabPageAdInfo::CreativeNewTabPageAdInfo(
    const CreativeAdInfo& creative_ad)
    : CreativeAdInfo(creative_ad) {}

CreativeNewTabPageAdInfo::CreativeNewTabPageAdInfo(
    const CreativeNewTabPageAdInfo& other) = default;

CreativeNewTabPageAdInfo& CreativeNewTabPageAdInfo::operator=(
    const CreativeNewTabPageAdInfo& other) = default;

CreativeNewTabPageAdInfo::CreativeNewTabPageAdInfo(
    CreativeNewTabPageAdInfo&& other) noexcept = default;

CreativeNewTabPageAdInfo& CreativeNewTabPageAdInfo::operator=(
    CreativeNewTabPageAdInfo&& other) noexcept = default;

CreativeNewTabPageAdInfo::~CreativeNewTabPageAdInfo() = default;

}  // namespace catsxp_ads
