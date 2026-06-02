/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_DAT_CACHE_MANAGER_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_DAT_CACHE_MANAGER_H_

#include <optional>

#include "base/files/file_path.h"
#include "base/functional/callback.h"
#include "base/memory/scoped_refptr.h"
#include "base/task/sequenced_task_runner.h"
#include "catsxp/components/catsxp_component_updater/browser/dat_file_util.h"

using catsxp_component_updater::DATFileDataBuffer;

namespace catsxp_shields {

// Manages DAT file caching for adblock engines. Handles reading cached DATs
// on startup and writing serialized engine data to disk.
class AdBlockDATCacheManager {
 public:
  explicit AdBlockDATCacheManager(const base::FilePath& profile_dir);
  ~AdBlockDATCacheManager();
  AdBlockDATCacheManager(const AdBlockDATCacheManager&) = delete;
  AdBlockDATCacheManager& operator=(const AdBlockDATCacheManager&) = delete;

  // Writes a serialized DAT buffer to disk atomically.
  // Calls |on_complete| with success/failure.
  void WriteDATFile(bool is_default_engine, DATFileDataBuffer dat);

  // Reads cached DAT files from disk. Calls |on_complete| with the results.
  void MaybeReadCachedDATFiles(
      base::OnceCallback<void(std::optional<DATFileDataBuffer>,
                              std::optional<DATFileDataBuffer>)> on_complete);

 private:
  base::FilePath cache_dir_;
  scoped_refptr<base::SequencedTaskRunner> task_runner_;
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_AD_BLOCK_DAT_CACHE_MANAGER_H_
