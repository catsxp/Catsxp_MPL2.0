/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKENS_DATABASE_TABLE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKENS_DATABASE_TABLE_H_

#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_table_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads::database::table {

using GetPaymentTokensCallback =
    base::OnceCallback<void(bool success,
                            const PaymentTokenList& payment_tokens)>;

// Persists unspent payment tokens that have been earned via ad confirmations
// and are awaiting redemption. Tokens are loaded from this table on startup to
// populate the in-memory cache, and written here on every add or removal.
class PaymentTokens final : public TableInterface {
 public:
  void Save(const PaymentTokenList& payment_tokens, ResultCallback callback);

  void Delete(const PaymentTokenInfo& payment_token, ResultCallback callback);
  void Delete(const PaymentTokenList& payment_tokens, ResultCallback callback);
  void DeleteAll(ResultCallback callback);

  void GetAll(GetPaymentTokensCallback callback) const;

  // TableInterface:
  void Create(const mojom::DBTransactionInfoPtr& mojom_db_transaction) override;
  void Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               int to_version) override;
};

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKENS_DATABASE_TABLE_H_
