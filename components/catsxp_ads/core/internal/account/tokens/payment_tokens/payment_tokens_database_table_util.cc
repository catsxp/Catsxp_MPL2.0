/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_tokens_database_table_util.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_type.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/ad_type.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/database/database_column_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::database::table {

PaymentTokenInfo PaymentTokenFromMojomRow(
    const mojom::DBRowInfoPtr& mojom_db_row) {
  CHECK(mojom_db_row);
  CHECK_EQ(5U, mojom_db_row->column_values_union.size());

  PaymentTokenInfo payment_token;
  payment_token.transaction_id = ColumnString(mojom_db_row, 0);
  payment_token.unblinded_token =
      cbr::UnblindedToken(ColumnString(mojom_db_row, 1));
  payment_token.public_key = cbr::PublicKey(ColumnString(mojom_db_row, 2));
  payment_token.confirmation_type =
      ToMojomConfirmationType(ColumnString(mojom_db_row, 3));
  payment_token.ad_type = ToMojomAdType(ColumnString(mojom_db_row, 4));
  return payment_token;
}

}  // namespace catsxp_ads::database::table
