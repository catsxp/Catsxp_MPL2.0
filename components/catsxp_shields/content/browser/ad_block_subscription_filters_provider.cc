/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/content/browser/ad_block_subscription_filters_provider.h"

#include <string>
#include <utility>

#include "base/logging.h"
#include "base/task/sequenced_task_runner.h"
#include "base/task/single_thread_task_runner.h"
#include "base/task/thread_pool.h"
#include "catsxp/components/catsxp_shields/core/browser/ad_block_filters_provider.h"
#include "catsxp/components/catsxp_shields/core/common/adblock/rs/src/lib.rs.h"
#include "components/prefs/pref_service.h"

namespace catsxp_shields {

namespace {

// static
void AddDATBufferToFilterSet(
    base::OnceCallback<void(const adblock::FilterListMetadata&)> on_metadata,
    DATFileDataBuffer buffer,
    const perfetto::Flow& flow,
    rust::Box<adblock::FilterSet>* filter_set) {
  TRACE_EVENT("catsxp.adblock",
              "AddDATBufferToFilterSet_SubscriptionFiltersProvider", flow);
  auto result = (*filter_set)->add_filter_list(buffer);
  if (result.result_kind == adblock::ResultKind::Success) {
    std::move(on_metadata).Run(result.value);
  } else {
    VLOG(0) << "Subscription list parsing failed: "
            << result.error_message.c_str();
  }
}

}  // namespace

AdBlockSubscriptionFiltersProvider::AdBlockSubscriptionFiltersProvider(
    AdBlockFiltersProviderManager* manager,
    base::FilePath list_file,
    base::RepeatingCallback<void(const adblock::FilterListMetadata&)>
        on_metadata_retrieved)
    : AdBlockFiltersProvider(false, manager),
      list_file_(list_file),
      on_metadata_retrieved_(on_metadata_retrieved) {}

AdBlockSubscriptionFiltersProvider::~AdBlockSubscriptionFiltersProvider() =
    default;

void AdBlockSubscriptionFiltersProvider::LoadFilterSet(
    base::OnceCallback<
        void(base::OnceCallback<void(rust::Box<adblock::FilterSet>*)>)> cb) {
  const auto flow = perfetto::Flow::FromPointer(this);
  TRACE_EVENT("catsxp.adblock",
              "AdBlockSubscriptionFiltersProvider::LoadFilterSet", flow);
  base::ThreadPool::PostTaskAndReplyWithResult(
      FROM_HERE, {base::MayBlock()},
      base::BindOnce(&catsxp_component_updater::ReadDATFileData, list_file_),
      base::BindOnce(&AdBlockSubscriptionFiltersProvider::OnDATFileDataReady,
                     weak_factory_.GetWeakPtr(), std::move(cb), flow));
}

std::string AdBlockSubscriptionFiltersProvider::GetNameForDebugging() {
  return "AdBlockSubscriptionFiltersProvider";
}

void AdBlockSubscriptionFiltersProvider::OnDATFileDataReady(
    base::OnceCallback<
        void(base::OnceCallback<void(rust::Box<adblock::FilterSet>*)>)> cb,
    const perfetto::Flow& flow,
    const DATFileDataBuffer& dat_buf) {
  TRACE_EVENT("catsxp.adblock",
              "AdBlockSubscriptionFiltersProvider::OnDATFileDataReady", flow);
  std::move(cb).Run(base::BindOnce(
      &AddDATBufferToFilterSet,
      base::BindOnce(
          [](scoped_refptr<base::SequencedTaskRunner> task_runner,
             base::RepeatingCallback<void(const adblock::FilterListMetadata&)>
                 on_metadata,
             const adblock::FilterListMetadata& metadata) {
            task_runner->PostTask(FROM_HERE,
                                  base::BindOnce(on_metadata, metadata));
          },
          base::SingleThreadTaskRunner::GetCurrentDefault(),
          on_metadata_retrieved_),
      dat_buf, flow));
}

void AdBlockSubscriptionFiltersProvider::OnListAvailable() {
  NotifyObservers(engine_is_default_);
}

}  // namespace catsxp_shields
