/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_DATABASE_TABLE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_DATABASE_TABLE_H_

#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_table_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads::database::table {

using GetConfirmationTokensCallback =
    base::OnceCallback<void(bool success,
                            const ConfirmationTokenList& confirmation_tokens)>;

// Persists unspent confirmation tokens that are pending assignment to an ad
// confirmation. Tokens are loaded from this table on startup to populate the
// in-memory cache, and written here on every add or removal.
class ConfirmationTokens final : public TableInterface {
 public:
  void Save(const ConfirmationTokenList& confirmation_tokens,
            ResultCallback callback);

  void Delete(const ConfirmationTokenInfo& confirmation_token,
              ResultCallback callback);
  void DeleteAll(ResultCallback callback);

  void GetAll(GetConfirmationTokensCallback callback) const;

  // TableInterface:
  void Create(const mojom::DBTransactionInfoPtr& mojom_db_transaction) override;
  void Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               int to_version) override;

};

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_DATABASE_TABLE_H_
