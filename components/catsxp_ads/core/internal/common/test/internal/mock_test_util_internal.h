/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_MOCK_TEST_UTIL_INTERNAL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_MOCK_TEST_UTIL_INTERNAL_H_

#include "base/files/file_path.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_client/test/ads_client_mock.h"

namespace catsxp_ads {

class AdsClientNotifier;

namespace test {

void MockAdsClientNotifierAddObserver(AdsClientMock& ads_client_mock,
                                      AdsClientNotifier& ads_client_notifier);
void MockNotifyPendingObservers(AdsClientMock& ads_client_mock,
                                AdsClientNotifier& ads_client_notifier);

void MockShowNotificationAd(AdsClientMock& ads_client_mock);
void MockCloseNotificationAd(AdsClientMock& ads_client_mock);

void MockSave(AdsClientMock& ads_client_mock);
void MockRemove(AdsClientMock& ads_client_mock);
void MockLoad(AdsClientMock& ads_client_mock,
              const base::FilePath& profile_path);

void MockLoadResourceComponent(AdsClientMock& ads_client_mock,
                               const base::FilePath& profile_path);

void MockFindProfilePref(const AdsClientMock& ads_client_mock);
void MockGetProfilePref(const AdsClientMock& ads_client_mock);
void MockSetProfilePref(const AdsClientMock& ads_client_mock,
                        AdsClientNotifier& ads_client_notifier);
void MockClearProfilePref(const AdsClientMock& ads_client_mock);
void MockHasProfilePrefPath(const AdsClientMock& ads_client_mock);

void MockFindLocalStatePref(const AdsClientMock& ads_client_mock);
void MockGetLocalStatePref(const AdsClientMock& ads_client_mock);
void MockSetLocalStatePref(const AdsClientMock& ads_client_mock,
                           AdsClientNotifier& ads_client_notifier);
void MockClearLocalStatePref(const AdsClientMock& ads_client_mock);
void MockHasLocalStatePrefPath(const AdsClientMock& ads_client_mock);

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_MOCK_TEST_UTIL_INTERNAL_H_
