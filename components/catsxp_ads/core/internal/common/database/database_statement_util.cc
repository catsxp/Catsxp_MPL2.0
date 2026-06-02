/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/database/database_statement_util.h"

#include "base/strings/string_number_conversions.h"
#include "base/time/time.h"
#include "sql/statement.h"

namespace catsxp_ads::database {

std::string TimeToSqlValueAsString(base::Time time) {
  return base::NumberToString(sql::Statement::TimeToSqlValue(time));
}

}  // namespace catsxp_ads::database
