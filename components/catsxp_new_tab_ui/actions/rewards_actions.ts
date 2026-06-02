/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { action } from 'typesafe-actions'
import { types } from '../constants/rewards_types'

export const onBalanceReport = (properties: { month: number, year: number, report: NewTab.RewardsBalanceReport }) => action(types.ON_BALANCE_REPORT, {
  month: properties.month,
  year: properties.year,
  report: properties.report
})

export const dismissNotification = (id: string) => action(types.DISMISS_NOTIFICATION, {
  id
})

export const onBalance = (balance?: number) => action(types.ON_BALANCE, {
  balance
})

export const onAdsAccountStatement = (adsAccountStatement: NewTab.AdsAccountStatement) => action(types.ON_ADS_ACCOUNT_STATEMENT, {
  adsAccountStatement
})

export const onCompleteReset = (success: boolean) => action(types.ON_COMPLETE_RESET, {
  success
})
