/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/strings/string_conversions_util.h"

namespace catsxp_ads {

namespace {

constexpr char kTrue[] = "true";
constexpr char kFalse[] = "false";

}  // namespace

std::string BoolToString(bool value) {
  return value ? kTrue : kFalse;
}

}  // namespace catsxp_ads
