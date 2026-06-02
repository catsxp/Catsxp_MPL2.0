/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TABS_TAB_MANAGER_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TABS_TAB_MANAGER_OBSERVER_H_

#include <cstdint>
#include <string>

#include "base/containers/span.h"
#include "base/observer_list_types.h"
#include "url/gurl.h"

namespace catsxp_ads {

struct TabInfo;

class TabManagerObserver : public base::CheckedObserver {
 public:
  // Invoked when a new `tab` is opened.
  virtual void OnDidOpenNewTab(const TabInfo& tab) {}

  // Invoked when the `tab` has loaded.
  virtual void OnTabDidLoad(const TabInfo& tab, int http_status_code) {}

  // Invoked when the tab specfied by `tab_id` changes focus.
  virtual void OnTabDidChangeFocus(int32_t tab_id) {}

  // Invoked when the `tab` is updated.
  virtual void OnTabDidChange(const TabInfo& tab) {}

  // Invoked when the text content for the tab specified by `tab_id` did change.
  virtual void OnTextContentDidChange(int32_t tab_id,
                                      base::span<const GURL> redirect_chain,
                                      const std::string& text) {}

  // Invoked when a tab is closed with the given `tab_id`.
  virtual void OnDidCloseTab(int32_t tab_id) {}

  // Invoked when media starts playing in a tab specified by `tab_id`.
  virtual void OnTabDidStartPlayingMedia(int32_t tab_id) {}

  // Invoked when media stops playing in a tab specified by `tab_id`.
  virtual void OnTabDidStopPlayingMedia(int32_t tab_id) {}
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TABS_TAB_MANAGER_OBSERVER_H_
