/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/services/bat_ads_service_factory_impl.h"

#include <memory>
#include <utility>

#include "base/feature_list.h"
#include "base/functional/bind.h"
#include "base/metrics/field_trial_params.h"
#include "base/task/single_thread_task_runner.h"
#include "base/task/single_thread_task_runner_thread_mode.h"
#include "base/task/thread_pool.h"
#include "base/time/time.h"
#include "catsxp/components/services/bat_ads/bat_ads_service_impl.h"
#include "content/public/browser/browser_thread.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/self_owned_receiver.h"

namespace catsxp_ads {

namespace {

BASE_FEATURE(kInProcessCatsxpAdsServiceFeature,
             "InProcessCatsxpAdsService",
             base::FEATURE_ENABLED_BY_DEFAULT);

constexpr base::FeatureParam<base::TimeDelta> kCatsxpAdsServiceStartupDelay{
    &kInProcessCatsxpAdsServiceFeature, "startup_delay", base::Seconds(3)};

// Binds the `receiver` to a new provider on a background task runner.
void BindInProcessBatAdsService(
    mojo::PendingReceiver<bat_ads::mojom::BatAdsService>
        bat_ads_service_pending_receiver) {
  mojo::MakeSelfOwnedReceiver(std::make_unique<bat_ads::BatAdsServiceImpl>(),
                              std::move(bat_ads_service_pending_receiver));
}

// Launches an in process Bat Ads Service.
mojo::Remote<bat_ads::mojom::BatAdsService> LaunchInProcessBatAdsService() {
  mojo::Remote<bat_ads::mojom::BatAdsService> bat_ads_service_remote;
  base::ThreadPool::CreateSingleThreadTaskRunner(
      {base::MayBlock(), base::WithBaseSyncPrimitives()},
      base::SingleThreadTaskRunnerThreadMode::DEDICATED)
      ->PostDelayedTask(
          FROM_HERE,
          base::BindOnce(&BindInProcessBatAdsService,
                         bat_ads_service_remote.BindNewPipeAndPassReceiver()),
          kCatsxpAdsServiceStartupDelay.Get());
  return bat_ads_service_remote;
}

}  // namespace

BatAdsServiceFactoryImpl::BatAdsServiceFactoryImpl() = default;

BatAdsServiceFactoryImpl::~BatAdsServiceFactoryImpl() = default;

mojo::Remote<bat_ads::mojom::BatAdsService> BatAdsServiceFactoryImpl::Launch()
    const {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  return LaunchInProcessBatAdsService();
}

}  // namespace catsxp_ads
