/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/reminder/reminder_util.h"

#include <ostream>
#include <string_view>

#include "base/check.h"
#include "base/notreached.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_constants.h"
#include "components/grit/catsxp_components_strings.h"
#include "ui/base/l10n/l10n_util.h"
#include "url/gurl.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kReminderNotificationAdPlacementId =
    "e64373ac-2ca5-4f6b-b497-1f1d7ccd40c8";
constexpr std::string_view kReminderNotificationAdTargetUrl =
    "https://www.catsxp.com/hc/en-us/articles/14648356808845";

}  // namespace

namespace {

base::DictValue BuildClickedSameAdMultipleTimesReminder() {
  return base::DictValue()
      .Set(kNotificationAdPlacementIdKey, kReminderNotificationAdPlacementId)
      .Set(kNotificationAdTitleKey,
           l10n_util::GetStringUTF16(
               IDS_CATSXP_ADS_NOTIFICATION_CLICKED_SAME_AD_MULTIPLE_TIMES_TITLE))
      .Set(kNotificationAdBodyKey,
           l10n_util::GetStringUTF16(
               IDS_CATSXP_ADS_NOTIFICATION_CLICKED_SAME_AD_MULTIPLE_TIMES_BODY))
      .Set(kNotificationAdTargetUrlKey, kReminderNotificationAdTargetUrl);
}

base::DictValue BuildExternalWalletConnectedReminder() {
  return base::DictValue()
      .Set(kNotificationAdPlacementIdKey, kReminderNotificationAdPlacementId)
      .Set(kNotificationAdTitleKey,
           l10n_util::GetStringUTF16(
               IDS_CATSXP_ADS_NOTIFICATION_EXTERNAL_WALLET_CONNECTED_TITLE))
      .Set(kNotificationAdBodyKey,
           l10n_util::GetStringUTF16(
               IDS_CATSXP_ADS_NOTIFICATION_EXTERNAL_WALLET_CONNECTED_BODY))
      .Set(kNotificationAdTargetUrlKey, kReminderNotificationAdTargetUrl);
}

}  // namespace

base::DictValue BuildReminder(mojom::ReminderType mojom_reminder_type) {
  switch (mojom_reminder_type) {
    case mojom::ReminderType::kClickedSameAdMultipleTimes: {
      return BuildClickedSameAdMultipleTimesReminder();
    }

    case mojom::ReminderType::kExternalWalletConnected: {
      return BuildExternalWalletConnectedReminder();
    }
  }

  NOTREACHED() << "Unexpected value for mojom::ReminderType: "
               << mojom_reminder_type;
}

bool IsReminder(const std::string& placement_id) {
  return placement_id == kReminderNotificationAdPlacementId;
}

GURL GetReminderTargetUrl() {
  return GURL(kReminderNotificationAdTargetUrl);
}

}  // namespace catsxp_ads
