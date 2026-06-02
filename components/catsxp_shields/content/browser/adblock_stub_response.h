/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_ADBLOCK_STUB_RESPONSE_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_ADBLOCK_STUB_RESPONSE_H_

#include <optional>
#include <string>

#include "services/network/public/mojom/url_response_head.mojom-forward.h"

namespace network {
struct ResourceRequest;
}  // namespace network

namespace catsxp_shields {

// Intercepts certain requests and blocks them by silently returning 200 OK
// and not allowing them to hit the network.
void MakeStubResponse(const std::optional<std::string>& data_url,
                      const network::ResourceRequest& request,
                      network::mojom::URLResponseHeadPtr* response,
                      std::string* data);

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_ADBLOCK_STUB_RESPONSE_H_
