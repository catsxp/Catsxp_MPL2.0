/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SYNC_QR_CODE_VALIDATOR_H_
#define CATSXP_COMPONENTS_CATSXP_SYNC_QR_CODE_VALIDATOR_H_

#include <string>

#include "base/time/time.h"

namespace catsxp_sync {

enum class QrCodeDataValidationResult {
  kValid = 0,
  kNotWellFormed = 1,
  kVersionNotRecognized = 2,
  kVersionDeprecated = 3,
  kExpired = 4,
  kValidForTooLong = 5,
};

class QrCodeDataValidator {
 public:
  static QrCodeDataValidationResult ValidateQrDataJson(
      const std::string& qr_data_string);

  static base::Time GetQRv1SunsetDay();

 private:
  static bool IsValidSeedHex(const std::string& seed_hex);
  static base::Time qr_v1_sunset_day_;
};

}  // namespace catsxp_sync

#endif  // CATSXP_COMPONENTS_CATSXP_SYNC_QR_CODE_VALIDATOR_H_
