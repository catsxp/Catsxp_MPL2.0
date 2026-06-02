/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_shields/ad_block_browser_test_helper.h"

#include <memory>
#include <utility>

#include "base/functional/bind.h"
#include "base/functional/callback_forward.h"
#include "base/memory/scoped_refptr.h"
#include "base/test/thread_test_helper.h"
#include "catsxp/browser/catsxp_browser_process.h"
#include "catsxp/components/catsxp_shields/content/browser/ad_block_service.h"
#include "catsxp/components/catsxp_shields/content/test/ad_block_service_test_observer.h"
#include "catsxp/components/catsxp_shields/content/test/ad_block_unit_test_helper.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"

namespace catsxp_shields {

bool WaitForAdBlockServiceThreads() {
  scoped_refptr<base::ThreadTestHelper> tr_helper(new base::ThreadTestHelper(
      g_catsxp_browser_process->ad_block_service()->GetTaskRunnerForTesting()));
  return tr_helper->Run();
}

AdBlockBrowserTestHelper::AdBlockBrowserTestHelper(
    base::RepeatingClosure callback)
    : callback_(std::move(callback)) {
  create_services_subscription_ =
      BrowserContextDependencyManager::GetInstance()
          ->RegisterCreateServicesCallbackForTesting(base::BindRepeating(
              &AdBlockBrowserTestHelper::SetUpAdBlockService,
              base::Unretained(this)));
}

AdBlockBrowserTestHelper::~AdBlockBrowserTestHelper() = default;

void AdBlockBrowserTestHelper::WaitForAdBlockEngineInitialLoad() {
  if (initial_observer_) {
    initial_observer_->WaitForDefault();
    initial_observer_.reset();
  }
}

void AdBlockBrowserTestHelper::SetUpAdBlockService(
    content::BrowserContext* context) {
  if (!initial_observer_) {
    // Attach before SetupAdBlockServiceForTesting posts
    // SetFilterListCatalog({}) so the observer is guaranteed to catch the
    // resulting OnFilterListLoaded. Tests that want to wait on the initial
    // build call WaitForAdBlockEngineInitialLoad() before registering any
    // TestFiltersProvider; other tests simply ignore it.
    initial_observer_ = std::make_unique<AdBlockServiceTestObserver>(
        g_catsxp_browser_process->ad_block_service());
  }
  SetupAdBlockServiceForTesting(g_catsxp_browser_process->ad_block_service());
  callback_.Run();
}

}  // namespace catsxp_shields
