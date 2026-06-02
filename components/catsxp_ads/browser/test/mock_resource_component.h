/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_MOCK_RESOURCE_COMPONENT_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_MOCK_RESOURCE_COMPONENT_H_

#include <string>

#include "catsxp/components/catsxp_ads/browser/component_updater/resource_component.h"
#include "catsxp/components/catsxp_ads/browser/test/fake_component_updater_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads::test {

class MockResourceComponent : public ResourceComponent {
 public:
  MockResourceComponent();

  MockResourceComponent(const MockResourceComponent&) = delete;
  MockResourceComponent& operator=(const MockResourceComponent&) = delete;

  ~MockResourceComponent() override;

  MOCK_METHOD(void,
              RegisterCountryComponent,
              (const std::string& country_code),
              (override));
  MOCK_METHOD(void, UnregisterCountryComponent, (), (override));
  MOCK_METHOD(void,
              RegisterLanguageComponent,
              (const std::string& language_code),
              (override));
  MOCK_METHOD(void, UnregisterLanguageComponent, (), (override));

 private:
  FakeComponentUpdaterDelegate fake_component_updater_delegate_;
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_MOCK_RESOURCE_COMPONENT_H_
