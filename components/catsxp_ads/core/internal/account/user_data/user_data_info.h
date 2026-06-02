/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_USER_DATA_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_USER_DATA_INFO_H_

#include "base/values.h"

namespace catsxp_ads {

struct UserDataInfo final {
  UserDataInfo();

  UserDataInfo(const UserDataInfo&);
  UserDataInfo& operator=(const UserDataInfo&);

  UserDataInfo(UserDataInfo&&) noexcept;
  UserDataInfo& operator=(UserDataInfo&&) noexcept;

  ~UserDataInfo();

  bool operator==(const UserDataInfo&) const = default;

  // User data that may change.
  base::DictValue dynamic;

  // User data that remains constant.
  base::DictValue fixed;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_USER_DATA_INFO_H_
