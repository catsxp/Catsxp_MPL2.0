/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_SERVICE_ADS_SERVICE_CALLBACK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_SERVICE_ADS_SERVICE_CALLBACK_H_

#include <optional>

#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace base {
class DictValue;
class ListValue;
}  // namespace base

// Callback types for the `AdsService` browser-layer interface. `AdsService`
// bridges the browser to the `Ads` core interface. This header is always-built
// and must not include headers that assert `ENABLE_CATSXP_ADS`.

namespace catsxp_ads {

using ResultCallback = base::OnceCallback<void(bool success)>;

using GetInternalsCallback =
    base::OnceCallback<void(std::optional<base::DictValue> internals)>;

using GetDiagnosticsCallback =
    base::OnceCallback<void(std::optional<base::ListValue> diagnostics)>;

using GetStatementOfAccountsCallback =
    base::OnceCallback<void(mojom::StatementInfoPtr mojom_statement)>;

using MaybeServeMojomNewTabPageAdCallback =
    base::OnceCallback<void(mojom::NewTabPageAdInfoPtr ad)>;

using MaybeGetSearchResultAdCallback = base::OnceCallback<void(
    mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad)>;

using GetAdHistoryForUICallback =
    base::OnceCallback<void(std::optional<base::ListValue> ad_history)>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_SERVICE_ADS_SERVICE_CALLBACK_H_
