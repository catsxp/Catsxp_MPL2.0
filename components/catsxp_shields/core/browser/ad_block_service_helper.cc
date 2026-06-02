/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/core/browser/ad_block_service_helper.h"

#include <optional>

#include "base/check.h"

namespace catsxp_shields {

// Merges the first CSP directive into the second one provided, if they exist.
//
// Distinct policies are merged with comma separators, according to
// https://www.w3.org/TR/CSP2/#implementation-considerations
void MergeCspDirectiveInto(std::optional<std::string> from,
                           std::optional<std::string>* into) {
  DCHECK(into);

  if (!from) {
    return;
  }

  if (!*into) {
    *into = from;
    return;
  }

  const std::string from_str = *from;
  const std::string into_str = **into;

  *into = std::optional<std::string>(from_str + ", " + into_str);
}

}  // namespace catsxp_shields
