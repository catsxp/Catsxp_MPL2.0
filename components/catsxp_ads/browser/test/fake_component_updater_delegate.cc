/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/test/fake_component_updater_delegate.h"

#include "base/strings/string_util.h"

namespace catsxp_ads::test {

FakeComponentUpdaterDelegate::FakeComponentUpdaterDelegate() = default;

FakeComponentUpdaterDelegate::~FakeComponentUpdaterDelegate() = default;

void FakeComponentUpdaterDelegate::Register(
    const std::string& /*component_name*/,
    const std::string& /*component_base64_public_key*/,
    base::OnceClosure registered_callback,
    catsxp_component_updater::CatsxpComponent::ReadyCallback /*ready_callback*/) {
  if (registered_callback) {
    std::move(registered_callback).Run();
  }
}

bool FakeComponentUpdaterDelegate::Unregister(
    const std::string& /*component_id*/) {
  return true;
}

scoped_refptr<base::SequencedTaskRunner>
FakeComponentUpdaterDelegate::GetTaskRunner() {
  return nullptr;
}

const std::string& FakeComponentUpdaterDelegate::locale() const {
  return base::EmptyString();
}

PrefService* FakeComponentUpdaterDelegate::local_state() {
  return nullptr;
}

}  // namespace catsxp_ads::test
