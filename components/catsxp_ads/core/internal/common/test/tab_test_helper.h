/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_TAB_TEST_HELPER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_TAB_TEST_HELPER_H_

#include <cstdint>
#include <map>
#include <optional>
#include <vector>

#include "base/memory/raw_ref.h"

class GURL;

namespace catsxp_ads {

class AdsClientNotifier;

namespace test {

// Encapsulates tab lifecycle simulation for test fixtures. Each method fires
// the corresponding `AdsClientNotifier` notifications.
class TabHelper final {
 public:
  explicit TabHelper(AdsClientNotifier& ads_client_notifier);

  TabHelper(const TabHelper&) = delete;
  TabHelper& operator=(const TabHelper&) = delete;

  ~TabHelper();

  void OpenTab(int32_t tab_id,
               const std::vector<GURL>& redirect_chain,
               int http_status_code);
  void NavigateToUrl(int32_t tab_id,
                     const std::vector<GURL>& redirect_chain,
                     int http_status_code);
  void SelectTab(int32_t tab_id);
  void CloseTab(int32_t tab_id);

 private:
  void SelectLastTab();

  const raw_ref<AdsClientNotifier> ads_client_notifier_;

  std::optional<int32_t> visible_tab_id_;
  std::map</*tab_id=*/int32_t, std::vector<GURL>> redirect_chains_;
};

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_TAB_TEST_HELPER_H_
