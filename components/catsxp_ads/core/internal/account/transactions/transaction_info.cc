/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"

#include <limits>

#include "base/numerics/ranges.h"

namespace catsxp_ads {

TransactionInfo::TransactionInfo() = default;

TransactionInfo::TransactionInfo(const TransactionInfo& other) = default;

TransactionInfo& TransactionInfo::operator=(const TransactionInfo& other) =
    default;

TransactionInfo::TransactionInfo(TransactionInfo&& other) noexcept = default;

TransactionInfo& TransactionInfo::operator=(TransactionInfo&& other) noexcept =
    default;

TransactionInfo::~TransactionInfo() = default;

bool TransactionInfo::operator==(const TransactionInfo& other) const {
  return id == other.id && created_at == other.created_at &&
         creative_instance_id == other.creative_instance_id &&
         segment == other.segment &&
         base::IsApproximatelyEqual(value, other.value,
                                    std::numeric_limits<double>::epsilon()) &&
         ad_type == other.ad_type &&
         confirmation_type == other.confirmation_type &&
         reconciled_at == other.reconciled_at;
}

bool TransactionInfo::IsValid() const {
  return !id.empty() && created_at && !creative_instance_id.empty() &&
         !segment.empty() && ad_type != mojom::AdType::kUndefined &&
         confirmation_type != mojom::ConfirmationType::kUndefined;
}

}  // namespace catsxp_ads
