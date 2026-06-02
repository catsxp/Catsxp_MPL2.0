/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_DEVICE_ID_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_DEVICE_ID_H_

#include "catsxp/components/catsxp_ads/browser/device_id/device_id.h"

namespace catsxp_ads::test {

// Defers the `GetDeviceId` callback until `Complete` is called. Because the
// callback installs pref change registrars and triggers the first
// `MaybeStartBatAdsService` evaluation, this lets tests control when the entire
// startup sequence begins.
class FakeDeviceId : public DeviceId {
 public:
  FakeDeviceId();

  FakeDeviceId(const FakeDeviceId&) = delete;
  FakeDeviceId& operator=(const FakeDeviceId&) = delete;

  ~FakeDeviceId() override;

  // DeviceId:
  void GetDeviceId(DeviceIdCallback callback) override;

  // Runs the captured callback with a device ID, completing the pending
  // request.
  void Complete();

 private:
  DeviceIdCallback callback_;
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_DEVICE_ID_H_
