/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_CLIENT_ADS_CLIENT_CALLBACK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_CLIENT_ADS_CLIENT_CALLBACK_H_

#include <optional>
#include <string>

#include "base/files/file.h"
#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/history/site_history.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

// Callback types for the `AdsClient` public interface. `AdsClient` is the
// outward-facing interface that `core` calls into the browser. This header
// asserts `ENABLE_CATSXP_ADS` and must not be included by always-built targets.

namespace catsxp_ads {

using ResultCallback = base::OnceCallback<void(bool success)>;

using LoadCallback =
    base::OnceCallback<void(const std::optional<std::string>& value)>;

using LoadFileCallback = base::OnceCallback<void(base::File file)>;

using UrlRequestCallback =
    base::OnceCallback<void(const mojom::UrlResponseInfo& mojom_url_response)>;

using GetSiteHistoryCallback =
    base::OnceCallback<void(const SiteHistoryList& site_history)>;

using GetScheduledCaptchaCallback =
    base::OnceCallback<void(const std::string& captcha_id)>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_CLIENT_ADS_CLIENT_CALLBACK_H_
