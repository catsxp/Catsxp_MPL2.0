/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_SHIELDS_CATSXP_SHIELDS_WEB_CONTENTS_OBSERVER_H_
#define CATSXP_BROWSER_CATSXP_SHIELDS_CATSXP_SHIELDS_WEB_CONTENTS_OBSERVER_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/containers/flat_map.h"
#include "base/synchronization/lock.h"
#include "catsxp/components/catsxp_shields/core/common/catsxp_shields.mojom.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "content/public/browser/render_frame_host_receiver_set.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

namespace content {
class WebContents;
}

class PrefRegistrySimple;

namespace catsxp_shields {

class CatsxpShieldsWebContentsObserver
    : public content::WebContentsObserver,
      public content::WebContentsUserData<CatsxpShieldsWebContentsObserver>,
      public catsxp_shields::mojom::CatsxpShieldsHost {
 public:
  explicit CatsxpShieldsWebContentsObserver(content::WebContents*);
  CatsxpShieldsWebContentsObserver(const CatsxpShieldsWebContentsObserver&) =
      delete;
  CatsxpShieldsWebContentsObserver& operator=(
      const CatsxpShieldsWebContentsObserver&) = delete;
  ~CatsxpShieldsWebContentsObserver() override;

  static void BindCatsxpShieldsHost(
      mojo::PendingAssociatedReceiver<catsxp_shields::mojom::CatsxpShieldsHost>
          receiver,
      content::RenderFrameHost* rfh);

  static void RegisterProfilePrefs(PrefRegistrySimple* registry);
  static void DispatchBlockedEventForWebContents(
      const std::string& block_type,
      const std::string& subresource,
      content::WebContents* web_contents);
  static void DispatchAllowedOnceEventForWebContents(
      const std::string& block_type,
      const std::string& subresource,
      content::WebContents* web_contents);
  static void DispatchWebcompatFeatureInvokedForWebContents(
      ContentSettingsType webcompat_content_settings,
      content::WebContents* web_contents);
  static void DispatchBlockedEvent(
      const GURL& request_url,
      content::GlobalRenderFrameHostToken render_frame_token,
      const std::string& block_type);
  void AllowScriptsOnce(const std::vector<std::string>& origins);
  void BlockAllowedScripts(const std::vector<std::string>& origins);
  bool IsBlockedSubresource(const std::string& subresource);
  void AddBlockedSubresource(const std::string& subresource);

 protected:
  // content::WebContentsObserver overrides.
  void ReadyToCommitNavigation(
      content::NavigationHandle* navigation_handle) override;

  // catsxp_shields::mojom::CatsxpShieldsHost.
  void OnJavaScriptBlocked(const std::u16string& details) override;
  void OnJavaScriptAllowedOnce(const std::u16string& details) override;
  void OnWebcompatFeatureInvoked(
      ContentSettingsType webcompat_settings_type) override;

 private:
  friend class content::WebContentsUserData<CatsxpShieldsWebContentsObserver>;
  friend class CatsxpShieldsWebContentsObserverBrowserTest;

  // Allows indicating a implementor of catsxp_shields::mojom::CatsxpShieldsHost
  // other than this own class, for testing purposes only.
  static void SetReceiverImplForTesting(CatsxpShieldsWebContentsObserver* impl);

  // Only used from the BindCatsxpShieldsHost() static method, useful to bind
  // the mojo receiver of catsxp_shields::mojom::CatsxpShieldsHost to a
  // different implementor when needed, for testing purposes.
  void BindReceiver(mojo::PendingAssociatedReceiver<
                        catsxp_shields::mojom::CatsxpShieldsHost> receiver,
                    content::RenderFrameHost* rfh);

  // Sends the current shields settings to the renderer process bound to the
  // given |navigation_handle|.
  void SendShieldsSettings(content::NavigationHandle* navigation_handle);

  std::vector<std::string> allowed_scripts_;
  // We keep a set of the current page's blocked URLs in case the page
  // continually tries to load the same blocked URLs.
  std::set<std::string> blocked_url_paths_;

  content::RenderFrameHostReceiverSet<catsxp_shields::mojom::CatsxpShieldsHost>
      receivers_;

  WEB_CONTENTS_USER_DATA_KEY_DECL();
};

}  // namespace catsxp_shields

#endif  // CATSXP_BROWSER_CATSXP_SHIELDS_CATSXP_SHIELDS_WEB_CONTENTS_OBSERVER_H_
