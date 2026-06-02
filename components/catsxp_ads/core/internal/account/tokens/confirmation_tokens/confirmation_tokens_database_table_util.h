/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_DATABASE_TABLE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_DATABASE_TABLE_UTIL_H_

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_token_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::database::table {

ConfirmationTokenInfo ConfirmationTokenFromMojomRow(
    const mojom::DBRowInfoPtr& mojom_db_row);

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_DATABASE_TABLE_UTIL_H_
