/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/sync/catsxp_sync_alerts_service.h"

#include "base/check.h"
#include "catsxp/browser/infobars/catsxp_sync_account_deleted_infobar_delegate.h"
#include "catsxp/components/catsxp_sync/catsxp_sync_prefs.h"
#include "build/build_config.h"

#if !BUILDFLAG(IS_ANDROID)
#include "catsxp/browser/infobars/sync_cannot_run_infobar_delegate.h"
#endif
#include "catsxp/components/sync/service/catsxp_sync_service_impl.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/sync/sync_service_factory.h"
#include "chrome/browser/ui/browser_finder.h"
#include "components/infobars/content/content_infobar_manager.h"

#if BUILDFLAG(IS_ANDROID)
#include "base/android/jni_android.h"
#include "catsxp/build/android/jni_headers/CatsxpSyncAccountDeletedInformer_jni.h"
#else
#include "chrome/browser/ui/browser.h"
#endif

using syncer::CatsxpSyncServiceImpl;
using syncer::SyncService;

CatsxpSyncAlertsService::CatsxpSyncAlertsService(Profile* profile)
    : profile_(profile) {
  if (SyncServiceFactory::IsSyncAllowed(profile)) {
    SyncService* service = SyncServiceFactory::GetForProfile(profile_);

    if (service) {
      DCHECK(!sync_service_observer_.IsObservingSource(service));
      sync_service_observer_.AddObservation(service);
    }
  }
}

CatsxpSyncAlertsService::~CatsxpSyncAlertsService() {}

void CatsxpSyncAlertsService::OnStateChanged(SyncService* service) {
  // Use profile prefs directly for boolean checks — safe regardless of whether
  // |service| is a CatsxpSyncServiceImpl or a test double (e.g.
  // TestSyncService).
  catsxp_sync::Prefs prefs(profile_->GetPrefs());

  if (prefs.IsSyncAccountDeletedNoticePending()) {
    ShowInfobar();
  }

#if !BUILDFLAG(IS_ANDROID)
  if (!prefs.IsFailedDecryptSeedNoticeDismissed() &&
      !prefs.GetEncryptedSeed().empty()) {
    // Only cast to CatsxpSyncServiceImpl here, after the early returns above
    // have already guarded us. In tests without a sync chain configured,
    // GetEncryptedSeed() is empty and we never reach this point.
    auto* catsxp_sync_service = static_cast<CatsxpSyncServiceImpl*>(service);
    auto seed = catsxp_sync_service->GetSeed();
    if (!seed.has_value() &&
        seed.error() ==
            syncer::CatsxpSyncServiceImpl::GetSeedStatusEnum::kDecryptFailed) {
      ShowSyncCannotRunInfobar();
    }
  }
#endif
}

void CatsxpSyncAlertsService::OnSyncShutdown(SyncService* sync_service) {
  if (sync_service_observer_.IsObservingSource(sync_service)) {
    sync_service_observer_.RemoveObservation(sync_service);
  }
}

void CatsxpSyncAlertsService::ShowSyncCannotRunInfobar() {
#if !BUILDFLAG(IS_ANDROID)
  BrowserWindowInterface* browser = chrome::FindLastActive();
  if (browser) {
    content::WebContents* active_web_contents =
        browser->GetTabStripModel()->GetActiveWebContents();
    if (active_web_contents) {
      infobars::ContentInfoBarManager* infobar_manager =
          infobars::ContentInfoBarManager::FromWebContents(active_web_contents);
      if (infobar_manager) {
        SyncCannotRunInfoBarDelegate::Create(infobar_manager, browser);
      }
    }
  }
#endif
}

void CatsxpSyncAlertsService::ShowInfobar() {
#if BUILDFLAG(IS_ANDROID)
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_CatsxpSyncAccountDeletedInformer_show(env);
#else
  BrowserWindowInterface* browser = chrome::FindLastActive();
  if (browser) {
    content::WebContents* active_web_contents =
        browser->GetTabStripModel()->GetActiveWebContents();
    if (active_web_contents) {
      CatsxpSyncAccountDeletedInfoBarDelegate::Create(active_web_contents,
                                                     profile_);
    }
  }
#endif
}
