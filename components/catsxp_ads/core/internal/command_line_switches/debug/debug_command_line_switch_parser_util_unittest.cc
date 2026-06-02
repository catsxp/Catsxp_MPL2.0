/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include <string>
#include <vector>

#include "base/strings/string_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/command_line_switch_test_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/command_line_switch_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

struct ParamInfo final {
  test::CommandLineSwitchInfo command_line_switch;
  bool should_debug = false;
};

std::vector<ParamInfo> GetTestCases() {
  return {
      {.command_line_switch = {"rewards", "debug=true"}, .should_debug = true},
      {.command_line_switch = {"rewards", "debug=1"}, .should_debug = true},
      {.command_line_switch = {"rewards", "debug=false"},
       .should_debug = false},
      {.command_line_switch = {"rewards", "debug=foobar"},
       .should_debug = false},
      {.command_line_switch = {}, .should_debug = false}};
}

}  // namespace

class CatsxpAdsDebugCommandLineSwitchParserUtilTest
    : public test::TestBase,
      public ::testing::WithParamInterface<ParamInfo> {
 protected:
  void SetUpMocks() override {
    test::AppendCommandLineSwitches({GetParam().command_line_switch});
  }
};

TEST_P(CatsxpAdsDebugCommandLineSwitchParserUtilTest,
       ParseDebugCommandLineSwitch) {
  // Act & Assert
  ASSERT_TRUE(GlobalState::HasInstance());
  EXPECT_EQ(GetParam().should_debug,
            GlobalState::GetInstance()->CommandLineSwitches().should_debug);
}

std::string TestParamToString(
    const ::testing::TestParamInfo<ParamInfo>& test_param) {
  const std::string should_debug =
      test_param.param.should_debug ? "ShouldDebug" : "ShouldNotDebug";

  const std::string sanitized_command_line_switch =
      test::ToString(test_param.param.command_line_switch);

  return base::ReplaceStringPlaceholders(
      "$1For$2", {should_debug, sanitized_command_line_switch}, nullptr);
}

INSTANTIATE_TEST_SUITE_P(,
                         CatsxpAdsDebugCommandLineSwitchParserUtilTest,
                         ::testing::ValuesIn(GetTestCases()),
                         TestParamToString);

}  // namespace catsxp_ads
