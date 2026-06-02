/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_CALLBACK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_CALLBACK_H_

#include <optional>

#include "base/functional/callback.h"
#include "base/types/optional_ref.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_info.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace base {
class DictValue;
class ListValue;
}  // namespace base

// Callback types for the `Ads` public interface. `Ads` is the core entry point
// that `AdsService` calls into. This header asserts `ENABLE_CATSXP_ADS` and must
// not be included by always-built targets.

namespace catsxp_ads {

using ResultCallback = base::OnceCallback<void(bool success)>;

using GetInternalsCallback =
    base::OnceCallback<void(std::optional<base::DictValue> internals)>;

using GetDiagnosticsCallback =
    base::OnceCallback<void(std::optional<base::ListValue> diagnostics)>;

using GetStatementOfAccountsCallback =
    base::OnceCallback<void(mojom::StatementInfoPtr mojom_statement)>;

using MaybeServeNewTabPageAdCallback =
    base::OnceCallback<void(base::optional_ref<const NewTabPageAdInfo> ad)>;

using MaybeGetNotificationAdCallback =
    base::OnceCallback<void(base::optional_ref<const NotificationAdInfo> ad)>;

using MaybeGetSearchResultAdCallback = base::OnceCallback<void(
    mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad)>;

using GetAdHistoryForUICallback =
    base::OnceCallback<void(std::optional<base::ListValue> ad_history)>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_CALLBACK_H_
