/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/confirmation_token_issuer_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/payment_token_issuer_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_value_util.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

namespace catsxp_ads {

void SetIssuers(const IssuersInfo& issuers) {
  SetProfileIntegerPref(prefs::kIssuerPing, issuers.ping);

  SetProfileListPref(prefs::kIssuers,
                     TokenIssuersToList(issuers.token_issuers));
}

std::optional<IssuersInfo> GetIssuers() {
  std::optional<base::ListValue> list = GetProfileListPref(prefs::kIssuers);
  if (!list || list->empty()) {
    return std::nullopt;
  }

  std::optional<TokenIssuerList> token_issuers =
      MaybeBuildTokenIssuersFromList(*list);
  if (!token_issuers) {
    return std::nullopt;
  }

  IssuersInfo issuers;
  issuers.ping = GetProfileIntegerPref(prefs::kIssuerPing);
  issuers.token_issuers = *token_issuers;

  return issuers;
}

bool IsIssuersValid(const IssuersInfo& issuers) {
  return IsConfirmationTokenIssuerValid(issuers) &&
         IsPaymentTokenIssuerValid(issuers);
}

bool HasIssuers() {
  return TokenIssuerExistsForType(TokenIssuerType::kConfirmations) &&
         TokenIssuerExistsForType(TokenIssuerType::kPayments);
}

bool HasIssuersChanged(const IssuersInfo& other) {
  std::optional<IssuersInfo> issuers = GetIssuers();
  if (!issuers) {
    return true;
  }

  return other != *issuers;
}

}  // namespace catsxp_ads
