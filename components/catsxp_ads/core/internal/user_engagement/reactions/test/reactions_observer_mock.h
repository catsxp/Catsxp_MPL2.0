/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_TEST_REACTIONS_OBSERVER_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_TEST_REACTIONS_OBSERVER_MOCK_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/reactions/reactions_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class ReactionsObserverMock : public ReactionsObserver {
 public:
  ReactionsObserverMock();

  ReactionsObserverMock(const ReactionsObserverMock&) = delete;
  ReactionsObserverMock& operator=(const ReactionsObserverMock&) = delete;

  ~ReactionsObserverMock() override;

  MOCK_METHOD(void, OnDidLikeAd, (const std::string&));
  MOCK_METHOD(void, OnDidDislikeAd, (const std::string&));

  MOCK_METHOD(void, OnDidLikeSegment, (const std::string&));
  MOCK_METHOD(void, OnDidDislikeSegment, (const std::string&));

  MOCK_METHOD(void, OnDidToggleSaveAd, (const std::string&));

  MOCK_METHOD(void, OnDidToggleMarkAdAsInappropriate, (const std::string&));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_TEST_REACTIONS_OBSERVER_MOCK_H_
