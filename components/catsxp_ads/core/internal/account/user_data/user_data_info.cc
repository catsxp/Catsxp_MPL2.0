/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/user_data_info.h"

namespace catsxp_ads {

UserDataInfo::UserDataInfo() = default;

UserDataInfo::UserDataInfo(const UserDataInfo& other) {
  *this = other;
}

UserDataInfo& UserDataInfo::operator=(const UserDataInfo& other) {
  if (this != &other) {
    dynamic = other.dynamic.Clone();
    fixed = other.fixed.Clone();
  }

  return *this;
}

UserDataInfo::UserDataInfo(UserDataInfo&& other) noexcept = default;

UserDataInfo& UserDataInfo::operator=(UserDataInfo&& other) noexcept = default;

UserDataInfo::~UserDataInfo() = default;

}  // namespace catsxp_ads
