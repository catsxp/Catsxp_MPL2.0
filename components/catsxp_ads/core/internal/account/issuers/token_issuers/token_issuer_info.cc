/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"

namespace catsxp_ads {

TokenIssuerInfo::TokenIssuerInfo() = default;

TokenIssuerInfo::TokenIssuerInfo(const TokenIssuerInfo& other) = default;

TokenIssuerInfo& TokenIssuerInfo::operator=(const TokenIssuerInfo& other) =
    default;

TokenIssuerInfo::TokenIssuerInfo(TokenIssuerInfo&& other) noexcept = default;

TokenIssuerInfo& TokenIssuerInfo::operator=(TokenIssuerInfo&& other) noexcept =
    default;

TokenIssuerInfo::~TokenIssuerInfo() = default;

}  // namespace catsxp_ads
