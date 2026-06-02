/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_OBLIVIOUS_HTTP_CONSTANTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_OBLIVIOUS_HTTP_CONSTANTS_H_

#include <string_view>

namespace catsxp_ads {

inline constexpr std::string_view kStagingObliviousHttpKeyConfigUrl =
    "https://static.ads.catsxpsoftware.com/v1/ohttp/hpkekeyconfig";
inline constexpr std::string_view kStagingObliviousHttpRelayUrl =
    "https://ohttp.ads.catsxpsoftware.com/v1/ohttp/gateway";

inline constexpr std::string_view kProductionObliviousHttpKeyConfigUrl =
    "https://static.ads.catsxp.com/v1/ohttp/hpkekeyconfig";
inline constexpr std::string_view kProductionObliviousHttpRelayUrl =
    "https://ohttp.ads.catsxp.com/v1/ohttp/gateway";

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_OBLIVIOUS_HTTP_CONSTANTS_H_
