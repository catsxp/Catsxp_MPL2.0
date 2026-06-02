/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state_holder.h"

#include "base/check.h"
#include "base/threading/sequence_local_storage_slot.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"

namespace catsxp_ads {

namespace {

GlobalState*& GetGlobalStateInstance() {
  static base::SequenceLocalStorageSlot<GlobalState*> global_state_instance;
  return global_state_instance.GetOrCreateValue();
}

}  // namespace

GlobalStateHolder::GlobalStateHolder(GlobalState* const global_state) {
  GlobalState*& global_state_instance = GetGlobalStateInstance();
  CHECK(!global_state_instance);
  global_state_instance = global_state;
}

GlobalStateHolder::~GlobalStateHolder() {
  GlobalState*& global_state_instance = GetGlobalStateInstance();
  CHECK(global_state_instance);
  global_state_instance = nullptr;
}

// static
GlobalState* GlobalStateHolder::GetGlobalState() {
  GlobalState* global_state_instance = GetGlobalStateInstance();
  return global_state_instance;
}

}  // namespace catsxp_ads
