/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SYNC_QR_CODE_DATA_H_
#define CATSXP_COMPONENTS_CATSXP_SYNC_QR_CODE_DATA_H_

#include <memory>
#include <string>

#include "base/time/time.h"
#include "base/values.h"

namespace catsxp_sync {

class QrCodeData {
 public:
  static constexpr int kCurrentQrCodeDataVersion = 2;
  static constexpr int kMinutesFromNowForValidCode = 30;

  int version;
  std::string sync_code_hex;
  base::Time not_after;

  static std::unique_ptr<QrCodeData> CreateWithActualDate(
      const std::string& sync_code_hex);

  std::string ToJson();
  static std::unique_ptr<QrCodeData> FromJson(const std::string& json_string);

  static base::Time FromEpochSeconds(int64_t seconds_since_epoch);
  static int64_t ToEpochSeconds(const base::Time& time);

 private:
  QrCodeData();
  QrCodeData(const std::string& sync_code_hex, const base::Time& not_after);

  base::DictValue ToValue() const;
};

}  // namespace catsxp_sync

#endif  // CATSXP_COMPONENTS_CATSXP_SYNC_QR_CODE_DATA_H_
