/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_GLOBAL_STATE_GLOBAL_STATE_HOLDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_GLOBAL_STATE_GLOBAL_STATE_HOLDER_H_

namespace catsxp_ads {

class GlobalState;

class GlobalStateHolder final {
 public:
  explicit GlobalStateHolder(GlobalState* global_state);

  GlobalStateHolder(const GlobalStateHolder& other) = delete;
  GlobalStateHolder& operator=(const GlobalStateHolder& other) = delete;

  GlobalStateHolder(GlobalStateHolder&& other) noexcept = delete;
  GlobalStateHolder& operator=(GlobalStateHolder&& other) noexcept = delete;

  ~GlobalStateHolder();

  static GlobalState* GetGlobalState();
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_GLOBAL_STATE_GLOBAL_STATE_HOLDER_H_
