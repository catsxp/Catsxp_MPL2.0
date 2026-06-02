/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_PUBLIC_KEY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_PUBLIC_KEY_H_

#include <optional>
#include <ostream>
#include <string>

#include "base/check.h"
#include "catsxp/components/challenge_bypass_ristretto/public_key.h"

namespace catsxp_ads::cbr {

// A `PublicKey` is a commitment by the server to a particular `SigningKey`.

class PublicKey final {
 public:
  PublicKey();
  explicit PublicKey(const std::string& public_key_base64);
  explicit PublicKey(const challenge_bypass_ristretto::PublicKey& public_key);

  PublicKey(const PublicKey&);
  PublicKey& operator=(const PublicKey&);

  PublicKey(PublicKey&&) noexcept;
  PublicKey& operator=(PublicKey&&) noexcept;

  ~PublicKey();

  bool operator==(const PublicKey&) const;

  bool has_value() const { return public_key_.has_value(); }

  challenge_bypass_ristretto::PublicKey& get() {
    CHECK(public_key_);
    return *public_key_;
  }

  const challenge_bypass_ristretto::PublicKey& get() const {
    CHECK(public_key_);
    return *public_key_;
  }

  static PublicKey DecodeBase64(const std::string& public_key_base64);
  std::optional<std::string> EncodeBase64() const;

 private:
  std::optional<challenge_bypass_ristretto::PublicKey> public_key_;
};

std::ostream& operator<<(std::ostream& os, const PublicKey& public_key);

}  // namespace catsxp_ads::cbr

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_PUBLIC_KEY_H_
