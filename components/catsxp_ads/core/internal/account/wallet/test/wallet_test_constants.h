/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_WALLET_TEST_WALLET_TEST_CONSTANTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_WALLET_TEST_WALLET_TEST_CONSTANTS_H_

namespace catsxp_ads::test {

inline constexpr char kWalletPaymentId[] =
    "27a39b2f-9b2e-4eb0-bbb2-2f84447496e7";

inline constexpr char kWalletRecoverySeedBase64[] =
    "x5uBvgI5MTTVY6sjGv65e9EHr8v7i+UxkFB9qVc5fP0=";
inline constexpr char kInvalidWalletRecoverySeed[] =
    "y6vCwhJ6NUUWZ7tkHw76f0FIs9w8j-VylGC0rWd6gQ1=";

inline constexpr char kWalletPublicKey[] =
    "BiG/i3tfNLSeOA9ZF5rkPCGyhkc7KCRbQS3bVGMvFQ0=";

inline constexpr char kWalletSecretKey[] =
    R"(kwUjEEdzI6rkI6hLoyxosa47ZrcZUvbYppAm4zvYF5gGIb+Le180tJ44D1kXmuQ8IbKGRzsoJFtBLdtUYy8VDQ==)";

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_WALLET_TEST_WALLET_TEST_CONSTANTS_H_
