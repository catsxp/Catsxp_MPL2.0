/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_tokens_database_table_util.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/database/database_column_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::database::table {

ConfirmationTokenInfo ConfirmationTokenFromMojomRow(
    const mojom::DBRowInfoPtr& mojom_db_row) {
  CHECK(mojom_db_row);
  CHECK_EQ(3U, mojom_db_row->column_values_union.size());

  ConfirmationTokenInfo confirmation_token;
  confirmation_token.unblinded_token =
      cbr::UnblindedToken(ColumnString(mojom_db_row, 0));
  confirmation_token.public_key = cbr::PublicKey(ColumnString(mojom_db_row, 1));
  confirmation_token.signature_base64 = ColumnString(mojom_db_row, 2);
  return confirmation_token;
}

}  // namespace catsxp_ads::database::table
