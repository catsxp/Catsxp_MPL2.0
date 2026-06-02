/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_info.h"

namespace catsxp_ads {

bool NotificationAdInfo::IsValid() const {
  return AdInfo::IsValid() && !title.empty() && !body.empty();
}

}  // namespace catsxp_ads
