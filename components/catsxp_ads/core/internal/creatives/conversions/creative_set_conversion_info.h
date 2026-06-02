/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_INFO_H_

#include <string>
#include <vector>

#include "base/time/time.h"

namespace catsxp_ads {

struct CreativeSetConversionInfo final {
  CreativeSetConversionInfo();

  CreativeSetConversionInfo(const CreativeSetConversionInfo&);
  CreativeSetConversionInfo& operator=(const CreativeSetConversionInfo&);

  CreativeSetConversionInfo(CreativeSetConversionInfo&&) noexcept;
  CreativeSetConversionInfo& operator=(CreativeSetConversionInfo&&) noexcept;

  ~CreativeSetConversionInfo();

  bool operator==(const CreativeSetConversionInfo&) const = default;

  [[nodiscard]] bool IsValid() const;

  std::string id;
  std::string url_pattern;
  base::TimeDelta observation_window;
  std::optional<base::Time> expire_at;
};

using CreativeSetConversionList = std::vector<CreativeSetConversionInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_INFO_H_
