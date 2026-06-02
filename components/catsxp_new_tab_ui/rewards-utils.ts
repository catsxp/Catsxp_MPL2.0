/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

export const getTotalContributions = (report: NewTab.RewardsBalanceReport) => {
  if (!report) {
    return 0.0
  }

  return report.tips + report.contribute + report.monthly
}
