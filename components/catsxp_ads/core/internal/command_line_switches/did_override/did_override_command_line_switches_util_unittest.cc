/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/did_override/did_override_command_line_switches_util.h"

#include <string>
#include <vector>

#include "base/strings/string_util.h"
#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/command_line_switch_test_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/command_line_switch_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

struct ParamInfo final {
  test::CommandLineSwitchInfo command_line_switch;
  bool did_override_command_line_switch = false;
};

std::vector<ParamInfo> GetTestCases() {
  return {{.command_line_switch = {"foobar", ""},
           .did_override_command_line_switch = false},
          {.command_line_switch = {"enable-automation", ""},
           .did_override_command_line_switch = true}};
}

}  // namespace

class CatsxpAdsDidOverrideCommandLineSwitchesUtilTest
    : public test::TestBase,
      public ::testing::WithParamInterface<ParamInfo> {
 protected:
  void SetUpMocks() override {
    test::AppendCommandLineSwitches({GetParam().command_line_switch});

    scoped_feature_list_.InitFromCommandLine(
        /*enable_features=*/GetParam().command_line_switch.value,
        /*disable_features=*/{});
  }

  base::test::ScopedFeatureList scoped_feature_list_;
};

TEST_P(CatsxpAdsDidOverrideCommandLineSwitchesUtilTest,
       DidOverrideCommandLineSwitches) {
  // Act & Assert
  EXPECT_EQ(GetParam().did_override_command_line_switch,
            DidOverrideCommandLineSwitches());
}

std::string TestParamToString(
    const ::testing::TestParamInfo<ParamInfo>& test_param) {
  const std::string did_override_command_line_switch =
      test_param.param.did_override_command_line_switch ? "DidOverride"
                                                        : "DidNotOverride";

  const std::string sanitized_command_line_switch =
      test::ToString(test_param.param.command_line_switch);

  return base::ReplaceStringPlaceholders(
      "Set$1CommandLineSwitchesFor$2",
      {did_override_command_line_switch, sanitized_command_line_switch},
      nullptr);
}

INSTANTIATE_TEST_SUITE_P(,
                         CatsxpAdsDidOverrideCommandLineSwitchesUtilTest,
                         ::testing::ValuesIn(GetTestCases()),
                         TestParamToString);

}  // namespace catsxp_ads
