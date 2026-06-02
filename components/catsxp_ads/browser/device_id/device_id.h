/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_DEVICE_ID_DEVICE_ID_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_DEVICE_ID_DEVICE_ID_H_

#include <string>

#include "base/functional/callback.h"

namespace base {
template <typename Signature>
class OnceCallback;
}  // namespace base

namespace catsxp_ads {

using DeviceIdCallback = base::OnceCallback<void(std::string device_id)>;

class DeviceId {
 public:
  DeviceId();

  DeviceId(const DeviceId&) = delete;
  DeviceId& operator=(const DeviceId&) = delete;

  virtual ~DeviceId();

  // Calls `callback` with a unique device identifier as argument. The device
  // identifier has the following characteristics:
  // 1. It is shared across users of a device.
  // 2. It is resilient to device reboots.
  // 3. It can be reset in *some* way by the user. In Particular, it *cannot* be
  //    based only on a MAC address of a physical device. The specific
  //    implementation varies across platforms, some of them requiring a round
  //    trip to the IO or FILE thread. "callback" will always be called on the
  //    UI thread though (sometimes directly if the implementation allows
  //    running on the UI thread). The returned value is
  //    HMAC_SHA256(`raw_device_id`), so that the actual device identifier value
  //    is not exposed directly to the caller.
  //
  // NOTE: This device id must never leave the device.
  virtual void GetDeviceId(DeviceIdCallback callback) = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_DEVICE_ID_DEVICE_ID_H_
