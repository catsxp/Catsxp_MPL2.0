
/* Copyright (c) 2024 The Catsxp Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_OBSERVER_H_

#include <string>

#include "base/observer_list_types.h"

namespace catsxp_ads {

class ReactionsObserver : public base::CheckedObserver {
 public:
  // Invoked when the user likes an ad.
  virtual void OnDidLikeAd(const std::string& advertiser_id) {}

  // Invoked when the user dislikes an ad.
  virtual void OnDidDislikeAd(const std::string& advertiser_id) {}

  // Invoked when the user likes a segment.
  virtual void OnDidLikeSegment(const std::string& segment) {}

  // Invoked when the user dislikes a segment.
  virtual void OnDidDislikeSegment(const std::string& segment) {}

  // Invoked when a user saves or unsaves an ad.
  virtual void OnDidToggleSaveAd(const std::string& creative_instance_id) {}

  // Invoked when a user marks an ad as inappropriate or appropriate.
  virtual void OnDidToggleMarkAdAsInappropriate(
      const std::string& creative_set) {}
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_OBSERVER_H_
