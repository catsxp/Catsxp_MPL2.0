/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_BLOCKED_DOMAIN_1PES_LIFETIME_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_BLOCKED_DOMAIN_1PES_LIFETIME_H_

#include <optional>
#include <utility>
#include <vector>

#include "base/functional/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "url/gurl.h"

namespace ephemeral_storage {
class EphemeralStorageService;
}  // namespace ephemeral_storage

namespace catsxp_shields {

// Manages the lifetime of auto-enabled 1PES mode (by DomainBlock feature).
// Each instance is shared by each 1PES-enabled top-level frame with the same
// BlockedDomain1PESLifetime::Key. When the last top-level frame holding a
// reference is destroyed or navigates to a non-blocked domain, 1PES will be
// disabled.
class BlockedDomain1PESLifetime final
    : public base::RefCounted<BlockedDomain1PESLifetime> {
 public:
  using Key = std::pair<ephemeral_storage::EphemeralStorageService*, GURL>;

  static scoped_refptr<BlockedDomain1PESLifetime> GetOrCreate(
      ephemeral_storage::EphemeralStorageService* ephemeral_storage_service,
      const GURL& url);

  explicit BlockedDomain1PESLifetime(const Key& key);

  void AddOnReadyCallback(base::OnceCallback<void(bool)> on_ready);

  base::WeakPtr<BlockedDomain1PESLifetime> AsWeakPtr();

 private:
  friend class RefCounted<BlockedDomain1PESLifetime>;
  ~BlockedDomain1PESLifetime();

  void Start1PESEnableRequest();
  void On1PESEnableRequestComplete(bool is_enabled);

  const Key key_;
  std::vector<base::OnceCallback<void(bool)>> on_ready_;
  std::optional<bool> is_1pes_enabled_;

  base::WeakPtrFactory<BlockedDomain1PESLifetime> weak_ptr_factory_{this};
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_BLOCKED_DOMAIN_1PES_LIFETIME_H_
