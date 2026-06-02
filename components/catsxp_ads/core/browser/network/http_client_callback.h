/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_HTTP_CLIENT_CALLBACK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_HTTP_CLIENT_CALLBACK_H_

#include "base/functional/callback_forward.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

using SendRequestCallback = base::OnceCallback<void(mojom::UrlResponseInfoPtr)>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_HTTP_CLIENT_CALLBACK_H_
