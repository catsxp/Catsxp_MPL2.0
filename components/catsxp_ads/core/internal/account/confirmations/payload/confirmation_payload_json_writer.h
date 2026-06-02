/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_PAYLOAD_CONFIRMATION_PAYLOAD_JSON_WRITER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_PAYLOAD_CONFIRMATION_PAYLOAD_JSON_WRITER_H_

#include <string>

namespace catsxp_ads {

struct ConfirmationInfo;

namespace json::writer {

std::string WriteConfirmationPayload(const ConfirmationInfo& confirmation);

}  // namespace json::writer

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_PAYLOAD_CONFIRMATION_PAYLOAD_JSON_WRITER_H_
