/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { action } from 'typesafe-actions'

// Constants
import { types } from '../constants/adblock_types'

export const enableFilterList = (uuid: string, enabled: boolean) =>
  action(types.ADBLOCK_ENABLE_FILTER_LIST, {
    uuid,
    enabled,
  })

export const getCustomFilters = () => action(types.ADBLOCK_GET_CUSTOM_FILTERS)

export const getRegionalLists = () => action(types.ADBLOCK_GET_REGIONAL_LISTS)

export const getListSubscriptions = () =>
  action(types.ADBLOCK_GET_LIST_SUBSCRIPTIONS)

export const onGetCustomFilters = (customFilters: string) =>
  action(types.ADBLOCK_ON_GET_CUSTOM_FILTERS, {
    customFilters,
  })

export const onGetRegionalLists = (regionalLists: AdBlock.FilterList[]) =>
  action(types.ADBLOCK_ON_GET_REGIONAL_LISTS, {
    regionalLists,
  })

export const onGetListSubscriptions = (
  listSubscriptions: AdBlock.SubscriptionInfo[],
) =>
  action(types.ADBLOCK_ON_GET_LIST_SUBSCRIPTIONS, {
    listSubscriptions,
  })

export const updateCustomFilters = (customFilters: string) =>
  action(types.ADBLOCK_UPDATE_CUSTOM_FILTERS, {
    customFilters,
  })

export const submitNewSubscription = (listUrl: string) =>
  action(types.ADBLOCK_SUBMIT_NEW_SUBSCRIPTION, {
    listUrl,
  })

export const setSubscriptionEnabled = (listUrl: string, enabled: boolean) =>
  action(types.ADBLOCK_SET_SUBSCRIPTION_ENABLED, {
    listUrl,
    enabled,
  })

export const deleteSubscription = (listUrl: string) =>
  action(types.ADBLOCK_DELETE_SUBSCRIPTION, {
    listUrl,
  })

export const refreshSubscription = (listUrl: string) =>
  action(types.ADBLOCK_REFRESH_SUBSCRIPTION, {
    listUrl,
  })

export const viewSubscriptionSource = (listUrl: string) =>
  action(types.ADBLOCK_VIEW_SUBSCRIPTION_SOURCE, {
    listUrl,
  })
