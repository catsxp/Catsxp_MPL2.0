/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/test/purchase_intent_test_helper.h"

#include <vector>

#include "base/test/run_until.h"
#include "url/gurl.h"

namespace catsxp_ads::test {

PurchaseIntentHelper::PurchaseIntentHelper() : processor_(resource_) {}

PurchaseIntentHelper::~PurchaseIntentHelper() = default;

void PurchaseIntentHelper::Simulate() {
  CHECK(base::test::RunUntil([this] { return resource_.IsLoaded(); }));

  const std::vector<GURL> urls = {
      GURL("https://www.catsxp.com/test?foo=bar"),
      GURL("https://basicattentiontoken.org/test?bar=foo"),
      GURL("https://www.catsxp.com/test?foo=bar")};

  for (const auto& url : urls) {
    processor_.Process(url);
  }
}

// static
SegmentList PurchaseIntentHelper::Expectation() {
  return {"segment 3", "segment 2"};
}

}  // namespace catsxp_ads::test
