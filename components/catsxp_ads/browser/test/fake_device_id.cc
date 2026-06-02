/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/test/fake_device_id.h"

#include <utility>

#include "base/check.h"
#include "base/functional/callback.h"

namespace catsxp_ads::test {

FakeDeviceId::FakeDeviceId() = default;

FakeDeviceId::~FakeDeviceId() = default;

void FakeDeviceId::GetDeviceId(DeviceIdCallback callback) {
  callback_ = std::move(callback);
}

void FakeDeviceId::Complete() {
  CHECK(callback_);
  std::move(callback_).Run(/*device_id=*/"foo");
}

}  // namespace catsxp_ads::test
