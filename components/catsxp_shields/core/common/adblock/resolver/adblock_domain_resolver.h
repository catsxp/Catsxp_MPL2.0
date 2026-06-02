/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_ADBLOCK_RESOLVER_ADBLOCK_DOMAIN_RESOLVER_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_ADBLOCK_RESOLVER_ADBLOCK_DOMAIN_RESOLVER_H_

#include <stdint.h>

#include <string>

namespace adblock {

struct DomainPosition;

DomainPosition resolve_domain_position(const std::string& host);

}  // namespace adblock

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_ADBLOCK_RESOLVER_ADBLOCK_DOMAIN_RESOLVER_H_
