/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/non_reward/test/redeem_non_reward_confirmation_test_util.h"

namespace catsxp_ads::test {

std::string BuildCreateNonRewardConfirmationUrlResponseBody() {
  return R"(
              {
                "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
                "createdAt" : "2020-04-20T10:27:11.717Z",
                "type" : "view",
                "modifiedAt" : "2020-04-20T10:27:11.717Z",
                "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6"
              })";
}

}  // namespace catsxp_ads::test
