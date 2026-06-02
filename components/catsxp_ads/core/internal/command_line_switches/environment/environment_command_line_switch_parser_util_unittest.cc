/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include <string>
#include <vector>

#include "base/strings/string_util.h"
#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/command_line_switches_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/environment/test/environment_types_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/command_line_switch_test_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/command_line_switch_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

struct ParamInfo final {
  test::CommandLineSwitchInfo command_line_switch;
  mojom::EnvironmentType environment_type = kDefaultEnvironmentType;
};

std::vector<ParamInfo> GetTestCases() {
  return {
      {.command_line_switch = {"rewards", "staging=true"},
       .environment_type = mojom::EnvironmentType::kStaging},
      {.command_line_switch = {"rewards", "staging=1"},
       .environment_type = mojom::EnvironmentType::kStaging},
      {.command_line_switch = {"rewards", "staging=false"},
       .environment_type = mojom::EnvironmentType::kProduction},
      {.command_line_switch = {"rewards", "staging=foobar"},
       .environment_type = mojom::EnvironmentType::kProduction},
      {.command_line_switch = {}, .environment_type = kDefaultEnvironmentType}};
}

}  // namespace

class CatsxpAdsEnvironmentCommandLineSwitchParserUtilTest
    : public test::TestBase,
      public ::testing::WithParamInterface<ParamInfo> {
 protected:
  void SetUpMocks() override {
    test::AppendCommandLineSwitches({GetParam().command_line_switch});
  }
};

TEST_P(CatsxpAdsEnvironmentCommandLineSwitchParserUtilTest,
       ParseEnvironmentCommandLineSwitch) {
  // Act & Assert
  ASSERT_TRUE(GlobalState::HasInstance());
  EXPECT_EQ(GetParam().environment_type,
            GlobalState::GetInstance()->CommandLineSwitches().environment_type);
}

std::string TestParamToString(
    const ::testing::TestParamInfo<ParamInfo>& test_param) {
  const std::string environment_type =
      test::ToString(test_param.param.environment_type);

  const std::string sanitized_command_line_switch =
      test::ToString(test_param.param.command_line_switch);

  return base::ReplaceStringPlaceholders(
      "$1EnvironmentFor$2", {environment_type, sanitized_command_line_switch},
      nullptr);
}

INSTANTIATE_TEST_SUITE_P(,
                         CatsxpAdsEnvironmentCommandLineSwitchParserUtilTest,
                         ::testing::ValuesIn(GetTestCases()),
                         TestParamToString);

}  // namespace catsxp_ads
