/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/test/mock_resource_component.h"

namespace catsxp_ads::test {

MockResourceComponent::MockResourceComponent()
    : ResourceComponent(&fake_component_updater_delegate_) {}

MockResourceComponent::~MockResourceComponent() = default;

}  // namespace catsxp_ads::test
