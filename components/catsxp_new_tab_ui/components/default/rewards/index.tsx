/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import createWidget from '../widget/index'
import { StyledCard, StyledTitleTab } from '../widgetCard'

import { LocaleContext } from '../../../../catsxp_rewards/resources/shared/lib/locale_context'
import { createLocaleContextForWebUI } from '../../../../catsxp_rewards/resources/shared/lib/webui_locale_context'
import { getProviderPayoutStatus } from '../../../../catsxp_rewards/resources/shared/lib/provider_payout_status'
import { userTypeFromString } from '../../../../catsxp_rewards/resources/shared/lib/user_type'
import {
  optional
} from '../../../../catsxp_rewards/resources/shared/lib/optional'

import {
  externalWalletFromExtensionData
} from '../../../../catsxp_rewards/resources/shared/lib/external_wallet'

import {
  RewardsCard,
  RewardsCardHeaderContent
} from '../../../../catsxp_rewards/resources/shared/components/newtab'

const locale = createLocaleContextForWebUI()

export interface RewardsProps {
  rewardsEnabled: boolean
  userType: string
  declaredCountry: string
  needsBrowserUpgradeToServeAds: boolean
  balance?: number
  externalWalletProviders?: string[]
  report?: NewTab.RewardsBalanceReport
  adsAccountStatement: NewTab.AdsAccountStatement
  parameters: NewTab.RewardsParameters
  totalContribution: number
  publishersVisitedCount: number
  selfCustodyInviteDismissed: boolean
  isTermsOfServiceUpdateRequired: boolean
  showContent: boolean
  stackPosition: number
  onShowContent: () => void
  onDismissNotification: (id: string) => void
  onSelfCustodyInviteDismissed: () => void
  onTermsOfServiceUpdateAccepted: () => void
}

export const RewardsWidget = createWidget((props: RewardsProps) => {
  if (!props.showContent) {
    return (
      <StyledTitleTab onClick={props.onShowContent}>
        <LocaleContext.Provider value={locale}>
          <RewardsCardHeaderContent />
        </LocaleContext.Provider>
      </StyledTitleTab>
    )
  }

  const adsInfo = props.adsAccountStatement || null
  const externalWallet = externalWalletFromExtensionData(null)

  const providerPayoutStatus = () => {
    const { payoutStatus } = props.parameters
    if (!payoutStatus) {
      return 'off'
    }
    const walletProvider = externalWallet ? externalWallet.provider : null
    return getProviderPayoutStatus(payoutStatus, walletProvider)
  }

  return (
    <LocaleContext.Provider value={locale}>
      <StyledCard>
        <RewardsCard
          rewardsEnabled={props.rewardsEnabled}
          userType={userTypeFromString(props.userType)}
          declaredCountry={props.declaredCountry}
          needsBrowserUpgradeToServeAds={props.needsBrowserUpgradeToServeAds}
          rewardsBalance={optional(props.balance)}
          exchangeCurrency='USD'
          exchangeRate={props.parameters.rate}
          providerPayoutStatus={providerPayoutStatus()}
          externalWallet={externalWallet}
          nextPaymentDate={adsInfo ? adsInfo.nextPaymentDate : 0}
          adsReceivedThisMonth={adsInfo ? adsInfo.adsReceivedThisMonth : 0}
          minEarningsThisMonth={adsInfo ? adsInfo.minEarningsThisMonth : 0}
          maxEarningsThisMonth={adsInfo ? adsInfo.maxEarningsThisMonth : 0}
          minEarningsLastMonth={adsInfo ? adsInfo.minEarningsLastMonth : 0}
          maxEarningsLastMonth={adsInfo ? adsInfo.maxEarningsLastMonth : 0}
          contributionsThisMonth={props.totalContribution}
          showSelfCustodyInvite={false}
          isTermsOfServiceUpdateRequired={props.isTermsOfServiceUpdateRequired}
          publishersVisited={props.publishersVisitedCount || 0}
          onEnableRewards={() => {}}
          onSelectCountry={() => {}}
          onSelfCustodyInviteDismissed={props.onSelfCustodyInviteDismissed}
          onTermsOfServiceUpdateAccepted={props.onTermsOfServiceUpdateAccepted}
        />
      </StyledCard>
    </LocaleContext.Provider>
  )
})
