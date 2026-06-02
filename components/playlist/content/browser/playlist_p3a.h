/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_PLAYLIST_P3A_H_
#define CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_PLAYLIST_P3A_H_

#include "base/memory/raw_ptr.h"
#include "base/time/time.h"
#include "base/timer/wall_clock_timer.h"

class PrefService;

namespace playlist {

inline constexpr char kLastUsageTimeHistogramName[] =
    "Catsxp.Playlist.LastUsageTime";
inline constexpr char kFirstTimeOffsetHistogramName[] =
    "Catsxp.Playlist.FirstTimeOffset";
inline constexpr char kUsageDaysInWeekHistogramName[] =
    "Catsxp.Playlist.UsageDaysInWeek";
inline constexpr char kNewUserReturningHistogramName[] =
    "Catsxp.Playlist.NewUserReturning";

// Manages P3A metrics for playlist
class PlaylistP3A {
 public:
  PlaylistP3A(PrefService* local_state, base::Time browser_first_run_time);
  ~PlaylistP3A();
  PlaylistP3A(const PlaylistP3A&) = delete;
  PlaylistP3A& operator=(PlaylistP3A&) = delete;

  void ReportNewUsage();

 private:
  void SetUpTimer();
  void Update(bool new_usage);

  raw_ptr<PrefService> local_state_;
  base::Time browser_first_run_time_;
  base::WallClockTimer update_timer_;
};

}  // namespace playlist

#endif  // CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_PLAYLIST_P3A_H_
