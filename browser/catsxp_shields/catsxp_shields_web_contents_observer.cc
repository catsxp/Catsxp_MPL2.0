/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_shields/catsxp_shields_web_contents_observer.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "base/check.h"
#include "base/feature_list.h"
#include "base/strings/utf_string_conversions.h"
#include "catsxp/browser/catsxp_shields/catsxp_shields_settings_service_factory.h"
#include "catsxp/components/catsxp_perf_predictor/browser/perf_predictor_tab_helper.h"
#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_settings_service.h"
#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_utils.h"
#include "catsxp/components/catsxp_shields/core/common/catsxp_shield_constants.h"
#include "catsxp/components/catsxp_shields/core/common/pref_names.h"
#include "catsxp/components/catsxp_shields/core/common/shields_settings.mojom.h"
#include "catsxp/components/constants/pref_names.h"
#include "catsxp/components/containers/buildflags/buildflags.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/renderer_configuration.mojom.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/render_process_host.h"
#include "content/public/browser/web_contents.h"
#include "extensions/buildflags/buildflags.h"
#include "mojo/public/cpp/bindings/associated_remote.h"
#include "third_party/blink/public/common/associated_interfaces/associated_interface_provider.h"

#if BUILDFLAG(ENABLE_CONTAINERS)
#include "catsxp/components/containers/content/browser/storage_partition_utils.h"
#include "catsxp/components/containers/core/common/features.h"
#endif

#if !BUILDFLAG(IS_ANDROID)
#include "catsxp/browser/catsxp_shields/catsxp_shields_tab_helper.h"
#endif

using content::NavigationHandle;
using content::RenderFrameHost;
using content::WebContents;

namespace catsxp_shields {

namespace {

CatsxpShieldsWebContentsObserver* g_receiver_impl_for_testing = nullptr;

bool IsJsBlockingEnforced(content::BrowserContext* browser_context,
                          const GURL& url) {
  Profile* profile = Profile::FromBrowserContext(browser_context);
  auto* settings_service =
      CatsxpShieldsSettingsServiceFactory::GetForProfile(profile);
  if (!settings_service) {
    return false;
  }

  return settings_service->IsJsBlockingEnforced(url);
}
}  // namespace

CatsxpShieldsWebContentsObserver::~CatsxpShieldsWebContentsObserver() = default;

CatsxpShieldsWebContentsObserver::CatsxpShieldsWebContentsObserver(
    WebContents* web_contents)
    : WebContentsObserver(web_contents),
      content::WebContentsUserData<CatsxpShieldsWebContentsObserver>(
          *web_contents),
      receivers_(web_contents, this) {}

bool CatsxpShieldsWebContentsObserver::IsBlockedSubresource(
    const std::string& subresource) {
  return blocked_url_paths_.find(subresource) != blocked_url_paths_.end();
}

void CatsxpShieldsWebContentsObserver::AddBlockedSubresource(
    const std::string& subresource) {
  blocked_url_paths_.insert(subresource);
}

// static
void CatsxpShieldsWebContentsObserver::BindCatsxpShieldsHost(
    mojo::PendingAssociatedReceiver<catsxp_shields::mojom::CatsxpShieldsHost>
        receiver,
    content::RenderFrameHost* rfh) {
  if (g_receiver_impl_for_testing) {
    g_receiver_impl_for_testing->BindReceiver(std::move(receiver), rfh);
    return;
  }

  auto* web_contents = content::WebContents::FromRenderFrameHost(rfh);
  if (!web_contents) {
    return;
  }

  auto* shields_host =
      CatsxpShieldsWebContentsObserver::FromWebContents(web_contents);
  if (!shields_host) {
    return;
  }
  shields_host->BindReceiver(std::move(receiver), rfh);
}

// static
void CatsxpShieldsWebContentsObserver::DispatchBlockedEvent(
    const GURL& request_url,
    content::GlobalRenderFrameHostToken render_frame_token,
    const std::string& block_type) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  auto* rfh = content::RenderFrameHost::FromFrameToken(render_frame_token);
  if (!rfh) {
    return;
  }

  auto subresource = request_url.spec();
  WebContents* web_contents = WebContents::FromRenderFrameHost(rfh);
  if (rfh->IsActive()) {
    DispatchBlockedEventForWebContents(block_type, subresource, web_contents);
  }

  if (web_contents) {
    CatsxpShieldsWebContentsObserver* observer =
        CatsxpShieldsWebContentsObserver::FromWebContents(web_contents);
    if (observer && !observer->IsBlockedSubresource(subresource)) {
      observer->AddBlockedSubresource(subresource);
      PrefService* prefs =
          Profile::FromBrowserContext(web_contents->GetBrowserContext())
              ->GetOriginalProfile()
              ->GetPrefs();

      if (block_type == kAds) {
        prefs->SetUint64(kAdsBlocked, prefs->GetUint64(kAdsBlocked) + 1);
      } else if (block_type == kHTTPUpgradableResources) {
        prefs->SetUint64(kHttpsUpgrades, prefs->GetUint64(kHttpsUpgrades) + 1);
      } else if (block_type == kJavaScript) {
        prefs->SetUint64(kJavascriptBlocked,
                         prefs->GetUint64(kJavascriptBlocked) + 1);
      } else if (block_type == kFingerprintingV2) {
        prefs->SetUint64(kFingerprintingBlocked,
                         prefs->GetUint64(kFingerprintingBlocked) + 1);
      }
    }
  }
  if (rfh->IsActive()) {
    catsxp_perf_predictor::PerfPredictorTabHelper::DispatchBlockedEvent(
        request_url.spec(), render_frame_token);
  }
}

#if !BUILDFLAG(IS_ANDROID)
// static
void CatsxpShieldsWebContentsObserver::DispatchBlockedEventForWebContents(
    const std::string& block_type,
    const std::string& subresource,
    WebContents* web_contents) {
  if (!web_contents) {
    return;
  }
  auto* shields_data_ctrlr =
      catsxp_shields::CatsxpShieldsTabHelper::FromWebContents(web_contents);
  // |shields_data_ctrlr| can be null if the |web_contents| is generated in
  // component layer - We don't attach any tab helpers in this case.
  if (!shields_data_ctrlr) {
    return;
  }
  shields_data_ctrlr->HandleItemBlocked(block_type, subresource);
}
// static
void CatsxpShieldsWebContentsObserver::DispatchAllowedOnceEventForWebContents(
    const std::string& block_type,
    const std::string& subresource,
    WebContents* web_contents) {
  if (!web_contents) {
    return;
  }
  auto* shields_data_ctrlr =
      catsxp_shields::CatsxpShieldsTabHelper::FromWebContents(web_contents);
  // |shields_data_ctrlr| can be null if the |web_contents| is generated in
  // component layer - We don't attach any tab helpers in this case.
  if (!shields_data_ctrlr) {
    return;
  }
  shields_data_ctrlr->HandleItemAllowedOnce(block_type, subresource);
}
// static
void CatsxpShieldsWebContentsObserver::
    DispatchWebcompatFeatureInvokedForWebContents(
        ContentSettingsType webcompat_content_settings,
        WebContents* web_contents) {
  if (!web_contents) {
    return;
  }
  auto* shields_data_ctrlr =
      catsxp_shields::CatsxpShieldsTabHelper::FromWebContents(web_contents);
  // |shields_data_ctrlr| can be null if the |web_contents| is generated in
  // component layer - We don't attach any tab helpers in this case.
  if (!shields_data_ctrlr) {
    return;
  }
  shields_data_ctrlr->HandleWebcompatFeatureInvoked(webcompat_content_settings);
}
#endif

void CatsxpShieldsWebContentsObserver::OnJavaScriptAllowedOnce(
    const std::u16string& details) {
#if !BUILDFLAG(IS_ANDROID)
  WebContents* web_contents =
      WebContents::FromRenderFrameHost(receivers_.GetCurrentTargetFrame());
  if (!web_contents) {
    return;
  }
  DispatchAllowedOnceEventForWebContents(
      catsxp_shields::kJavaScript, base::UTF16ToUTF8(details), web_contents);
#endif
}

void CatsxpShieldsWebContentsObserver::OnWebcompatFeatureInvoked(
    ContentSettingsType webcompat_settings_type) {
#if !BUILDFLAG(IS_ANDROID)
  WebContents* web_contents =
      WebContents::FromRenderFrameHost(receivers_.GetCurrentTargetFrame());
  if (!web_contents) {
    return;
  }
  DispatchWebcompatFeatureInvokedForWebContents(webcompat_settings_type,
                                                web_contents);
#endif
}

void CatsxpShieldsWebContentsObserver::OnJavaScriptBlocked(
    const std::u16string& details) {
  WebContents* web_contents =
      WebContents::FromRenderFrameHost(receivers_.GetCurrentTargetFrame());
  if (!web_contents) {
    return;
  }
  DispatchBlockedEventForWebContents(catsxp_shields::kJavaScript,
                                     base::UTF16ToUTF8(details), web_contents);
}

// static
void CatsxpShieldsWebContentsObserver::RegisterProfilePrefs(
    PrefRegistrySimple* registry) {
  registry->RegisterUint64Pref(kAdsBlocked, 0);
  registry->RegisterUint64Pref(kTrackersBlocked, 0);
  registry->RegisterUint64Pref(kJavascriptBlocked, 0);
  registry->RegisterUint64Pref(kHttpsUpgrades, 0);
  registry->RegisterUint64Pref(kFingerprintingBlocked, 0);
}

void CatsxpShieldsWebContentsObserver::ReadyToCommitNavigation(
    NavigationHandle* navigation_handle) {
  // Ignore same document navigations.
  if (navigation_handle->IsSameDocument()) {
    return;
  }

  // When the main frame navigates away.
  content::ReloadType reload_type = navigation_handle->GetReloadType();
  if (navigation_handle->IsInMainFrame()) {
    if (reload_type == content::ReloadType::NONE) {
      // For new loads, we reset the counters for both blocked scripts and URLs.
      allowed_scripts_.clear();
      blocked_url_paths_.clear();
    } else if (reload_type == content::ReloadType::NORMAL) {
      // For normal reloads (or loads to the current URL, internally converted
      // into reloads i.e see NavigationControllerImpl::NavigateWithoutEntry),
      // we only reset the counter for blocked URLs, not the one for scripts.
      blocked_url_paths_.clear();
    }
  }

  SendShieldsSettings(navigation_handle);
}

void CatsxpShieldsWebContentsObserver::BlockAllowedScripts(
    const std::vector<std::string>& scripts) {
  for (const auto& script : scripts) {
    auto origin = url::Origin::Create(GURL(script));
    bool is_origin = origin.Serialize() == script;
    std::erase_if(allowed_scripts_, [is_origin, script,
                                     origin](const std::string& value) {
      // scripts array may have both origins or full scripts paths.
      return is_origin ? url::Origin::Create(GURL(value)) == origin
                       : value == script;
    });
  }
}

void CatsxpShieldsWebContentsObserver::AllowScriptsOnce(
    const std::vector<std::string>& origins) {
  allowed_scripts_.insert(std::end(allowed_scripts_), std::begin(origins),
                          std::end(origins));
}

// static
void CatsxpShieldsWebContentsObserver::SetReceiverImplForTesting(
    CatsxpShieldsWebContentsObserver* impl) {
  g_receiver_impl_for_testing = impl;
}

void CatsxpShieldsWebContentsObserver::SendShieldsSettings(
    NavigationHandle* navigation_handle) {
  DCHECK(navigation_handle);
  RenderFrameHost* rfh = navigation_handle->GetRenderFrameHost();

  const GURL& primary_url =
      navigation_handle->GetParentFrameOrOuterDocument()
          ? navigation_handle->GetParentFrameOrOuterDocument()
                ->GetOutermostMainFrame()
                ->GetLastCommittedURL()
          : navigation_handle->GetURL();

  HostContentSettingsMap* host_content_settings_map =
      HostContentSettingsMapFactory::GetForProfile(rfh->GetBrowserContext());
  const catsxp_shields::mojom::FarblingLevel farbling_level =
      catsxp_shields::GetFarblingLevel(host_content_settings_map, primary_url);
  std::string additional_entropy;
#if BUILDFLAG(ENABLE_CONTAINERS)
  if (base::FeatureList::IsEnabled(containers::features::kContainers)) {
    additional_entropy = containers::GetContainerIdForWebContents(
        navigation_handle->GetWebContents());
  }
#endif
  const base::Token farbling_token =
      farbling_level != catsxp_shields::mojom::FarblingLevel::OFF
          ? catsxp_shields::GetFarblingToken(
                host_content_settings_map, primary_url,
                base::as_byte_span(additional_entropy))
          : base::Token();
  PrefService* pref_service =
      user_prefs::UserPrefs::Get(rfh->GetBrowserContext());

  mojo::AssociatedRemote<catsxp_shields::mojom::CatsxpShields> agent;
  rfh->GetRemoteAssociatedInterfaces()->GetInterface(&agent);
  agent->SetShieldsSettings(catsxp_shields::mojom::ShieldsSettings::New(
      farbling_level, farbling_token, allowed_scripts_,
      catsxp_shields::IsReduceLanguageEnabledForProfile(pref_service),
      IsJsBlockingEnforced(rfh->GetBrowserContext(), primary_url)));
}

void CatsxpShieldsWebContentsObserver::BindReceiver(
    mojo::PendingAssociatedReceiver<catsxp_shields::mojom::CatsxpShieldsHost>
        receiver,
    content::RenderFrameHost* rfh) {
  receivers_.Bind(rfh, std::move(receiver));
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(CatsxpShieldsWebContentsObserver);

}  // namespace catsxp_shields
