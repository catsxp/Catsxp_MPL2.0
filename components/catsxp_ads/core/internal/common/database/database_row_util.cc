/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/database/database_row_util.h"

#include <utility>

#include "base/check.h"
#include "base/containers/span.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::database {

mojom::DBRowInfoPtr CreateRow(
    sql::Statement* const statement,
    base::span<const mojom::DBBindColumnType> mojom_db_bind_column_types) {
  CHECK(statement);

  mojom::DBRowInfoPtr mojom_db_row = mojom::DBRowInfo::New();

  int column = 0;

  for (const auto& mojom_column_binding_type : mojom_db_bind_column_types) {
    mojom::DBColumnValueUnionPtr mojom_column_value_union;

    switch (mojom_column_binding_type) {
      case mojom::DBBindColumnType::kString: {
        mojom_column_value_union = mojom::DBColumnValueUnion::NewStringValue(
            statement->ColumnString(column));
        break;
      }

      case mojom::DBBindColumnType::kInt: {
        mojom_column_value_union = mojom::DBColumnValueUnion::NewIntValue(
            statement->ColumnInt(column));
        break;
      }

      case mojom::DBBindColumnType::kInt64: {
        mojom_column_value_union = mojom::DBColumnValueUnion::NewInt64Value(
            statement->ColumnInt64(column));
        break;
      }

      case mojom::DBBindColumnType::kDouble: {
        mojom_column_value_union = mojom::DBColumnValueUnion::NewDoubleValue(
            statement->ColumnDouble(column));
        break;
      }

      case mojom::DBBindColumnType::kBool: {
        mojom_column_value_union = mojom::DBColumnValueUnion::NewBoolValue(
            statement->ColumnBool(column));
        break;
      }

      case mojom::DBBindColumnType::kTime: {
        mojom_column_value_union = mojom::DBColumnValueUnion::NewTimeValue(
            statement->ColumnTime(column));
        break;
      }

      case mojom::DBBindColumnType::kTimeDelta: {
        mojom_column_value_union = mojom::DBColumnValueUnion::NewTimeDeltaValue(
            statement->ColumnTimeDelta(column));
        break;
      }
    }

    mojom_db_row->column_values_union.push_back(
        std::move(mojom_column_value_union));
    ++column;
  }

  return mojom_db_row;
}

}  // namespace catsxp_ads::database
