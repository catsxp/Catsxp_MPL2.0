/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/content/browser/ad_block_localhost_filters_provider.h"

#include <utility>
#include <vector>

#include "base/task/single_thread_task_runner.h"
#include "catsxp/components/catsxp_component_updater/browser/dat_file_util.h"

namespace catsxp_shields {

namespace {

constexpr uint8_t kLocalhostBadfilters[] = R"(
||0.0.0.0^$third-party,domain=~[::]|~[::ffff:0:0],badfilter
||[::]^$third-party,domain=~0.0.0.0|~[::ffff:0:0],badfilter
||[::ffff:0:0]^$third-party,domain=~0.0.0.0|~[::],badfilter
||localhost^$third-party,domain=~127.0.0.1|~[::1]|~[::ffff:7f00:1],badfilter
||127.0.0.1^$third-party,domain=~localhost|~[::1]|~[::ffff:7f00:1],badfilter
||[::1]^$third-party,domain=~localhost|~127.0.0.1|~[::ffff:7f00:1],badfilter
||[::ffff:7f00:1]^$third-party,domain=~localhost|~127.0.0.1|~[::1],badfilter
)";

void AddDATBufferToFilterSet(rust::Box<adblock::FilterSet>* filter_set) {
  (*filter_set)
      ->add_filter_list(std::vector<uint8_t>(std::begin(kLocalhostBadfilters),
                                             std::end(kLocalhostBadfilters)));
}

}  // namespace

AdBlockLocalhostFiltersProvider::AdBlockLocalhostFiltersProvider(
    AdBlockFiltersProviderManager* manager)
    : AdBlockFiltersProvider(true, manager) {
  NotifyObservers(engine_is_default_);
}

AdBlockLocalhostFiltersProvider::~AdBlockLocalhostFiltersProvider() = default;

std::string AdBlockLocalhostFiltersProvider::GetNameForDebugging() {
  return "AdBlockLocalhostFiltersProvider";
}

void AdBlockLocalhostFiltersProvider::LoadFilterSet(
    base::OnceCallback<
        void(base::OnceCallback<void(rust::Box<adblock::FilterSet>*)>)> cb) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  // PostTask so this has an async return to match other loaders
  base::SingleThreadTaskRunner::GetCurrentDefault()->PostTask(
      FROM_HERE,
      base::BindOnce(std::move(cb), base::BindOnce(&AddDATBufferToFilterSet)));
}

}  // namespace catsxp_shields
