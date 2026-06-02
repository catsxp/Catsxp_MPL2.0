/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TEST_CONVERSIONS_OBSERVER_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TEST_CONVERSIONS_OBSERVER_MOCK_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class ConversionsObserverMock : public ConversionsObserver {
 public:
  ConversionsObserverMock();

  ConversionsObserverMock(const ConversionsObserverMock&) = delete;
  ConversionsObserverMock& operator=(const ConversionsObserverMock&) = delete;

  ~ConversionsObserverMock() override;

  MOCK_METHOD(void, OnDidConvertAd, (const ConversionInfo&));
  MOCK_METHOD(void, OnFailedToConvertAd, (const std::string&));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TEST_CONVERSIONS_OBSERVER_MOCK_H_
