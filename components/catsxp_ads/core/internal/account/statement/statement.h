/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_H_

#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

using BuildStatementCallback =
    base::OnceCallback<void(mojom::StatementInfoPtr mojom_statement)>;

void BuildStatement(BuildStatementCallback callback);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_H_
