/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTION_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTION_INFO_H_

#include <optional>
#include <string>
#include <vector>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-shared.h"

namespace catsxp_ads {

struct TransactionInfo final {
  TransactionInfo();

  TransactionInfo(const TransactionInfo&);
  TransactionInfo& operator=(const TransactionInfo&);

  TransactionInfo(TransactionInfo&&) noexcept;
  TransactionInfo& operator=(TransactionInfo&&) noexcept;

  ~TransactionInfo();

  bool operator==(const TransactionInfo&) const;

  [[nodiscard]] bool IsValid() const;

  std::string id;
  std::optional<base::Time> created_at;
  std::string creative_instance_id;
  std::string segment;
  double value = 0.0;
  mojom::AdType ad_type = mojom::AdType::kUndefined;
  mojom::ConfirmationType confirmation_type =
      mojom::ConfirmationType::kUndefined;
  std::optional<base::Time> reconciled_at;
};

using TransactionList = std::vector<TransactionInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTION_INFO_H_
