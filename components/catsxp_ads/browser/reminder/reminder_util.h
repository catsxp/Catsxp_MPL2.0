/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_REMINDER_REMINDER_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_REMINDER_REMINDER_UTIL_H_

#include <stdint.h>

#include <string>

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

class GURL;

namespace catsxp_ads {
namespace mojom {
enum class ReminderType : int32_t;
}  // namespace mojom

base::DictValue BuildReminder(mojom::ReminderType mojom_reminder_type);

bool IsReminder(const std::string& placement_id);

GURL GetReminderTargetUrl();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_REMINDER_REMINDER_UTIL_H_
