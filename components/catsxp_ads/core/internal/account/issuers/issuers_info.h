/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_INFO_H_

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"

namespace catsxp_ads {

struct IssuersInfo final {
  IssuersInfo();

  IssuersInfo(const IssuersInfo&);
  IssuersInfo& operator=(const IssuersInfo&);

  IssuersInfo(IssuersInfo&&) noexcept;
  IssuersInfo& operator=(IssuersInfo&&) noexcept;

  ~IssuersInfo();

  bool operator==(const IssuersInfo&) const = default;

  int ping = 0;
  TokenIssuerList token_issuers;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_INFO_H_
