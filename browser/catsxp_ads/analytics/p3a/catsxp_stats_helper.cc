/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/analytics/p3a/catsxp_stats_helper.h"

#include "base/files/file_path.h"
#include "base/functional/bind.h"
#include "catsxp/browser/catsxp_stats/first_run_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "catsxp/components/p3a_utils/bucket.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/common/pref_names.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace catsxp_ads {

namespace {

constexpr int kAdsEnabledInstallationHourBuckets[] = {0, 11, 23, 71};

}  // namespace

CatsxpStatsHelper::CatsxpStatsHelper(PrefService& local_state,
                                   ProfileManager* profile_manager)
    : local_state_(local_state), profile_manager_(profile_manager) {
#if !BUILDFLAG(IS_ANDROID)
  last_used_profile_pref_change_registrar_.Init(&*local_state_);
  last_used_profile_pref_change_registrar_.Add(
      ::prefs::kProfileLastUsed,
      base::BindRepeating(&CatsxpStatsHelper::OnLastUsedProfileChanged,
                          base::Unretained(this)));
#endif

  profile_manager_observer_.Observe(profile_manager_);
}

CatsxpStatsHelper::~CatsxpStatsHelper() = default;

void CatsxpStatsHelper::RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  registry->RegisterBooleanPref(prefs::kEnabledForLastProfile, false);
  registry->RegisterBooleanPref(prefs::kEverEnabledForAnyProfile, false);
}

void CatsxpStatsHelper::OnProfileAdded(Profile* profile) {
#if BUILDFLAG(IS_ANDROID)
  if (profile == ProfileManager::GetPrimaryUserProfile()) {
#else
  base::FilePath last_used_path =
      local_state_->GetFilePath(::prefs::kProfileLastUsed);
  if ((!last_used_path.empty() && profile->GetBaseName() == last_used_path) ||
      (last_used_path.empty() &&
       profile == ProfileManager::GetLastUsedProfile())) {
#endif
    OnLastUsedProfileChanged();
  }
}

void CatsxpStatsHelper::OnProfileWillBeDestroyed(Profile* profile) {
  if (!current_profile_observation_.IsObservingSource(profile)) {
    return;
  }
  current_profile_observation_.Reset();
#if !BUILDFLAG(IS_ANDROID)
  last_used_profile_pref_change_registrar_.RemoveAll();
#endif
  ads_enabled_pref_change_registrar_.RemoveAll();
}

void CatsxpStatsHelper::OnProfileManagerDestroying() {
  if (current_profile_observation_.IsObserving()) {
#if !BUILDFLAG(IS_ANDROID)
    last_used_profile_pref_change_registrar_.RemoveAll();
#endif
    ads_enabled_pref_change_registrar_.RemoveAll();
    current_profile_observation_.Reset();
  }
  profile_manager_observer_.Reset();
}

void CatsxpStatsHelper::SetFirstRunTimeForTesting(base::Time time) {
  testing_first_run_time_ = time;
}

PrefService* CatsxpStatsHelper::GetLastUsedProfilePrefs() {
#if BUILDFLAG(IS_ANDROID)
  return ProfileManager::GetPrimaryUserProfile()->GetPrefs();
#else

  base::FilePath last_used_profile_path =
      local_state_->GetFilePath(::prefs::kProfileLastUsed);
  Profile* profile;
  if (last_used_profile_path.empty()) {
    profile = profile_manager_->GetLastUsedProfile();
  } else {
    profile = profile_manager_->GetProfileByPath(
        profile_manager_->user_data_dir().Append(last_used_profile_path));
  }
  if (profile == nullptr || profile->IsOffTheRecord()) {
    return nullptr;
  }
  if (current_profile_observation_.IsObserving()) {
    current_profile_observation_.Reset();
  }
  current_profile_observation_.Observe(profile);
  return profile->GetPrefs();
#endif
}

void CatsxpStatsHelper::OnLastUsedProfileChanged() {
  PrefService* profile_prefs = GetLastUsedProfilePrefs();
  if (profile_prefs == nullptr) {
    return;
  }
  ads_enabled_pref_change_registrar_.RemoveAll();
  ads_enabled_pref_change_registrar_.Init(profile_prefs);
  ads_enabled_pref_change_registrar_.Add(
      prefs::kOptedInToNotificationAds,
      base::BindRepeating(&CatsxpStatsHelper::Update, base::Unretained(this)));
  Update();
}

void CatsxpStatsHelper::Update() {
  PrefService* profile_prefs = GetLastUsedProfilePrefs();
  if (profile_prefs == nullptr) {
    return;
  }
  bool is_enabled = profile_prefs->GetBoolean(prefs::kOptedInToNotificationAds);
  UpdateLocalStateAdsEnabled(is_enabled);
  MaybeReportAdsInstallationTimeMetric(is_enabled);
}

void CatsxpStatsHelper::UpdateLocalStateAdsEnabled(
    bool is_enabled_for_current_profile) {
  // Copying enabled pref to local state so the stats updater does not depend on
  // the profile
  local_state_->SetBoolean(prefs::kEnabledForLastProfile,
                           is_enabled_for_current_profile);
}

void CatsxpStatsHelper::MaybeReportAdsInstallationTimeMetric(
    bool is_enabled_for_current_profile) {
  if (!is_enabled_for_current_profile ||
      local_state_->GetBoolean(prefs::kEverEnabledForAnyProfile)) {
    // If ads was already enabled for a previous profile or the current profile,
    // assume the metric was already sent.
    return;
  }
  local_state_->SetBoolean(prefs::kEverEnabledForAnyProfile, true);

  base::Time first_run = !testing_first_run_time_.is_null()
                             ? testing_first_run_time_
                             : catsxp_stats::GetFirstRunTime(&*local_state_);
  int hours_from_first_run = (base::Time::Now() - first_run).InHours();

  p3a_utils::RecordToHistogramBucket(kAdsEnabledInstallationTimeHistogramName,
                                     kAdsEnabledInstallationHourBuckets,
                                     hours_from_first_run);
}

}  // namespace catsxp_ads
