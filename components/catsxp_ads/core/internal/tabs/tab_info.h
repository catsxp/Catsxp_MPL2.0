/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TABS_TAB_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TABS_TAB_INFO_H_

#include <cstdint>
#include <vector>

#include "url/gurl.h"

namespace catsxp_ads {

struct TabInfo final {
  TabInfo();
  TabInfo(int32_t id,
          bool is_visible,
          std::vector<GURL> redirect_chain,
          bool is_playing_media);

  TabInfo(const TabInfo&);
  TabInfo& operator=(const TabInfo&);

  TabInfo(TabInfo&&) noexcept;
  TabInfo& operator=(TabInfo&&) noexcept;

  ~TabInfo();

  bool operator==(const TabInfo&) const = default;

  int32_t id = 0;
  bool is_visible = false;
  std::vector<GURL> redirect_chain;
  bool is_playing_media = false;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TABS_TAB_INFO_H_
