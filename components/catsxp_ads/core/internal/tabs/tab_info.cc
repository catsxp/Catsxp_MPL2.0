/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/tabs/tab_info.h"

#include <utility>

namespace catsxp_ads {

TabInfo::TabInfo() = default;

TabInfo::TabInfo(int32_t id,
                 bool is_visible,
                 std::vector<GURL> redirect_chain,
                 bool is_playing_media)
    : id(id),
      is_visible(is_visible),
      redirect_chain(std::move(redirect_chain)),
      is_playing_media(is_playing_media) {}

TabInfo::TabInfo(const TabInfo& other) = default;

TabInfo& TabInfo::operator=(const TabInfo& other) = default;

TabInfo::TabInfo(TabInfo&& other) noexcept = default;

TabInfo& TabInfo::operator=(TabInfo&& other) noexcept = default;

TabInfo::~TabInfo() = default;

}  // namespace catsxp_ads
