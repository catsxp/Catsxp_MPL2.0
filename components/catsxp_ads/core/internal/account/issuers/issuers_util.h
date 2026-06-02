/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_UTIL_H_

#include <optional>

namespace catsxp_ads {

struct IssuersInfo;

void SetIssuers(const IssuersInfo& issuers);
std::optional<IssuersInfo> GetIssuers();

bool IsIssuersValid(const IssuersInfo& issuers);

bool HasIssuers();
bool HasIssuersChanged(const IssuersInfo& other);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_UTIL_H_
