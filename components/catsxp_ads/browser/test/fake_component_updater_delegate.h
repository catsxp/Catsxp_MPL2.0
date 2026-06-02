/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_COMPONENT_UPDATER_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_COMPONENT_UPDATER_DELEGATE_H_

#include <string>

#include "base/functional/callback.h"
#include "base/memory/scoped_refptr.h"
#include "base/task/sequenced_task_runner.h"
#include "catsxp/components/catsxp_component_updater/browser/catsxp_component.h"

class PrefService;

namespace catsxp_ads::test {

// Minimal no-op `CatsxpComponent::Delegate` for use in unit tests that need a
// `ResourceComponent` without a real component updater.
class FakeComponentUpdaterDelegate final
    : public catsxp_component_updater::CatsxpComponent::Delegate {
 public:
  FakeComponentUpdaterDelegate();

  FakeComponentUpdaterDelegate(const FakeComponentUpdaterDelegate&) = delete;
  FakeComponentUpdaterDelegate& operator=(const FakeComponentUpdaterDelegate&) =
      delete;

  ~FakeComponentUpdaterDelegate() override;

  void Register(const std::string& /*component_name*/,
                const std::string& /*component_base64_public_key*/,
                base::OnceClosure registered_callback,
                catsxp_component_updater::CatsxpComponent::ReadyCallback
                /*ready_callback*/) override;

  bool Unregister(const std::string& /*component_id*/) override;

  void EnsureInstalled(const std::string& /*component_id*/) override {}

  void AddObserver(catsxp_component_updater::CatsxpComponent::ComponentObserver*
                   /*observer*/) override {}

  void RemoveObserver(
      catsxp_component_updater::CatsxpComponent::ComponentObserver*
      /*observer*/) override {}

  scoped_refptr<base::SequencedTaskRunner> GetTaskRunner() override;

  const std::string& locale() const override;

  PrefService* local_state() override;
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_COMPONENT_UPDATER_DELEGATE_H_
