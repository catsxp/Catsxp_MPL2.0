/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "base/test/scoped_feature_list.h"
#include "base/test/task_environment.h"
#include "base/time/time.h"
#include "content/public/test/render_view_test.h"
#include "third_party/blink/public/common/features.h"

using blink::features::kCatsxpRoundTimeStamps;

class CatsxpTimeStampRoundingRenderViewTest
    : public content::RenderViewTest,
      public ::testing::WithParamInterface<bool> {
 public:
  CatsxpTimeStampRoundingRenderViewTest() {}

  ~CatsxpTimeStampRoundingRenderViewTest() override = default;

  bool IsCatsxpRoundTimeStampsEnabled() { return GetParam(); }

  void SetUp() override {
    if (IsCatsxpRoundTimeStampsEnabled()) {
      scoped_feature_list_.InitAndEnableFeature(kCatsxpRoundTimeStamps);
    } else {
      scoped_feature_list_.InitAndDisableFeature(kCatsxpRoundTimeStamps);
    }
    RenderViewTest::SetUp();
  }

  double ExecuteJSAndReturnDouble(const std::u16string& script) {
    double result;
    EXPECT_TRUE(ExecuteJavaScriptAndReturnNumberValue(script, &result));
    return result;
  }

  void CheckRounded(const std::u16string& script, bool expect_rounded) {
    double result = ExecuteJSAndReturnDouble(script);
    if (expect_rounded) {
      EXPECT_DOUBLE_EQ(round(result) - result, 0);
    } else {
      EXPECT_NE(round(result) - result, 0);
    }
  }

  void Advance100Microseconds() {
    task_environment_.AdvanceClock(base::Microseconds(100));
  }

 protected:
  base::test::ScopedFeatureList scoped_feature_list_;
};

TEST_P(CatsxpTimeStampRoundingRenderViewTest, SynchronousApisRounded) {
  bool expect_rounded = IsCatsxpRoundTimeStampsEnabled();
  LoadHTML("<html><body>hi</body></html>");
  Advance100Microseconds();
  CheckRounded(u"performance.now()", expect_rounded);
  Advance100Microseconds();
  CheckRounded(u"performance.mark('test').startTime", expect_rounded);
  Advance100Microseconds();
  if (expect_rounded) {
    CheckRounded(u"performance.timeOrigin", true);
  }
}

INSTANTIATE_TEST_SUITE_P(CatsxpTimeStampRoundingRenderViewTest,
                         CatsxpTimeStampRoundingRenderViewTest,
                         ::testing::Bool());
