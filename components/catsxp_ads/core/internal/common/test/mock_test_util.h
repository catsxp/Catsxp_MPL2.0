/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_MOCK_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_MOCK_TEST_UTIL_H_

#include <string>
#include <utility>
#include <vector>

#include "base/containers/flat_map.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_client/test/ads_client_mock.h"
#include "catsxp/components/catsxp_ads/core/public/history/site_history.h"

// Helpers for configuring `AdsClientMock` default behaviors in tests via
// `ON_CALL`.
namespace catsxp_ads::test {

using URLResponsePair =
    std::pair</*response_status_code*/ int, /*response_body*/ std::string>;
using URLResponseList = std::vector<URLResponsePair>;
using URLResponseMap =
    base::flat_map</*url_request_path*/ std::string, URLResponseList>;

void MockIsNetworkConnectionAvailable(const AdsClientMock& ads_client_mock,
                                      bool is_available);

void MockIsBrowserActive(const AdsClientMock& ads_client_mock, bool is_active);
void MockIsBrowserInFullScreenMode(const AdsClientMock& ads_client_mock,
                                   bool is_full_screen_mode);

void MockCanShowNotificationAds(const AdsClientMock& ads_client_mock,
                                bool can_show);
void MockCanShowNotificationAdsWhileBrowserIsBackgrounded(
    const AdsClientMock& ads_client_mock,
    bool can_show);

void MockGetSiteHistory(const AdsClientMock& ads_client_mock,
                        const SiteHistoryList& site_history);

void MockUrlResponses(const AdsClientMock& ads_client_mock,
                      const URLResponseMap& url_responses);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_MOCK_TEST_UTIL_H_
