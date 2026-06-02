/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/browser/network/http_client_util.h"

#include "catsxp/components/catsxp_ads/core/browser/network/oblivious_http_constants.h"
#include "net/traffic_annotation/network_traffic_annotation.h"
#include "url/gurl.h"

namespace catsxp_ads {

GURL ObliviousHttpKeyConfigUrl(bool use_staging) {
  return GURL(use_staging ? kStagingObliviousHttpKeyConfigUrl
                          : kProductionObliviousHttpKeyConfigUrl);
}

GURL ObliviousHttpRelayUrl(bool use_staging) {
  return GURL(use_staging ? kStagingObliviousHttpRelayUrl
                          : kProductionObliviousHttpRelayUrl);
}

net::NetworkTrafficAnnotationTag GetNetworkTrafficAnnotationTag() {
  return net::DefineNetworkTrafficAnnotation("catsxp_ads", R"(
      semantics {
        sender: "Catsxp Ads"
        description:
          "This service is used to communicate with Catsxp servers "
          "to send and retrieve information for Ads."
        trigger:
          "Triggered by user viewing ads or at various intervals."
        data:
          "Ads catalog and Confirmations."
        destination: WEBSITE
      }
      policy {
        cookies_allowed: NO
        setting:
          "You can enable or disable this feature by visiting catsxp://rewards."
        policy_exception_justification:
          "Not implemented."
      }
    )");
}

}  // namespace catsxp_ads
