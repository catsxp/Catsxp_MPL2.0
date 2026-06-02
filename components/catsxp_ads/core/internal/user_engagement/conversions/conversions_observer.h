/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_OBSERVER_H_

#include <string>

#include "base/observer_list_types.h"

namespace catsxp_ads {

struct ConversionInfo;

class ConversionsObserver : public base::CheckedObserver {
 public:
  // Invoked when an ad has converted.
  virtual void OnDidConvertAd(const ConversionInfo& conversion) {}

  // Invoked when an ad fails to convert.
  virtual void OnFailedToConvertAd(const std::string& creative_instance_id) {}
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_OBSERVER_H_
