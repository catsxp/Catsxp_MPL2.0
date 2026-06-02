/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_ANALYTICS_P3A_CATSXP_STATS_HELPER_H_
#define CATSXP_BROWSER_CATSXP_ADS_ANALYTICS_P3A_CATSXP_STATS_HELPER_H_

#include "base/memory/raw_ptr.h"
#include "base/memory/raw_ref.h"
#include "base/scoped_observation.h"
#include "base/time/time.h"
#include "chrome/browser/profiles/profile_manager_observer.h"
#include "chrome/browser/profiles/profile_observer.h"
#include "components/prefs/pref_change_registrar.h"

class PrefRegistrySimple;
class PrefService;
class ProfileManager;
class Profile;

namespace catsxp_ads {
inline constexpr char kAdsEnabledInstallationTimeHistogramName[] =
    "Catsxp.Rewards.EnabledInstallationTime";

class CatsxpStatsHelper : public ProfileManagerObserver, public ProfileObserver {
 public:
  CatsxpStatsHelper(PrefService& local_state, ProfileManager* profile_manager);
  ~CatsxpStatsHelper() override;

  static void RegisterLocalStatePrefs(PrefRegistrySimple* registry);

  // ProfileManagerObserver:
  void OnProfileAdded(Profile* profile) override;
  void OnProfileManagerDestroying() override;

  // ProfileObserver:
  void OnProfileWillBeDestroyed(Profile* profile) override;

  void SetFirstRunTimeForTesting(base::Time time);

 private:
  PrefService* GetLastUsedProfilePrefs();
  void OnLastUsedProfileChanged();

  void Update();
  void UpdateLocalStateAdsEnabled(bool is_enabled_for_current_profile);
  void MaybeReportAdsInstallationTimeMetric(
      bool is_enabled_for_current_profile);

#if !BUILDFLAG(IS_ANDROID)
  PrefChangeRegistrar last_used_profile_pref_change_registrar_;
#endif
  PrefChangeRegistrar ads_enabled_pref_change_registrar_;
  base::ScopedObservation<Profile, ProfileObserver>
      current_profile_observation_{this};

  base::ScopedObservation<ProfileManager, ProfileManagerObserver>
      profile_manager_observer_{this};

  const raw_ref<PrefService> local_state_;
  const raw_ptr<ProfileManager> profile_manager_;  // Not owned.

  base::Time testing_first_run_time_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_ANALYTICS_P3A_CATSXP_STATS_HELPER_H_
