/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_DEVICE_ID_DEVICE_ID_IMPL_H_
#define CATSXP_BROWSER_CATSXP_ADS_DEVICE_ID_DEVICE_ID_IMPL_H_

#include "base/containers/span.h"
#include "catsxp/components/catsxp_ads/browser/device_id/device_id.h"

namespace catsxp_ads {

class DeviceIdImpl final : public DeviceId {
 public:
  // DeviceId:
  void GetDeviceId(DeviceIdCallback callback) override;

  // On some platforms, part of the machine ID is the MAC address. This function
  // is shared across platforms to filter out MAC addresses that have been
  // identified as invalid, i.e. not unique. For example, some VM hosts assign a
  // new MAC address at each reboot.
  static bool IsValidMacAddress(base::span<const uint8_t> bytes);

 private:
  // Platform specific implementation of "raw" device id retrieval.
  static void GetRawDeviceId(DeviceIdCallback callback);
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_DEVICE_ID_DEVICE_ID_IMPL_H_
