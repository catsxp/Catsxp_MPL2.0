/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_HTTP_CLIENT_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_HTTP_CLIENT_UTIL_H_

class GURL;

namespace net {
struct NetworkTrafficAnnotationTag;
}  // namespace net

namespace catsxp_ads {

// Returns the OHTTP key config URL corresponding to the staging or production
// environment, depending on `use_staging`.
GURL ObliviousHttpKeyConfigUrl(bool use_staging);

// Returns the OHTTP relay URL corresponding to the staging or production
// environment, depending on `use_staging`.
GURL ObliviousHttpRelayUrl(bool use_staging);

// Returns the network traffic annotation tag used to identify and audit network
// requests.
net::NetworkTrafficAnnotationTag GetNetworkTrafficAnnotationTag();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_HTTP_CLIENT_UTIL_H_
