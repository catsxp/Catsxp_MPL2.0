/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/crypto/key_pair_info.h"

namespace catsxp_ads::crypto {

KeyPairInfo::KeyPairInfo() = default;

KeyPairInfo::KeyPairInfo(const KeyPairInfo& other) = default;

KeyPairInfo& KeyPairInfo::operator=(const KeyPairInfo& other) = default;

KeyPairInfo::KeyPairInfo(KeyPairInfo&& other) noexcept = default;

KeyPairInfo& KeyPairInfo::operator=(KeyPairInfo&& other) noexcept = default;

KeyPairInfo::~KeyPairInfo() = default;

bool KeyPairInfo::IsValid() const {
  return !public_key.empty() && !secret_key.empty();
}

}  // namespace catsxp_ads::crypto
