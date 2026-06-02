/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import createWidget, { WidgetProps } from '../widget/index'
import { StyledCard, StyledTitleTab } from '../widgetCard'
import { VPNMainWidget, VPNPromoWidget, VPNWidgetTitle } from '../vpn/vpn_card'
import { CatsxpVPNState } from 'components/catsxp_new_tab_ui/reducers/catsxp_vpn'
import * as CatsxpVPN from '../../../api/catsxpVpn'
import { useNewTabPref } from '../../../hooks/usePref'

export interface VPNProps {
  showContent: boolean
  onShowContent: () => void
  catsxpVPNState: CatsxpVPNState
}

const VPNWidgetInternal = createWidget((props: VPNProps) => {
  if (!props.showContent) {
    return (
      <StyledTitleTab onClick={props.onShowContent}>
        <VPNWidgetTitle />
      </StyledTitleTab>
    )
  }

  return (
    <StyledCard>
      {props.catsxpVPNState.purchasedState ===
      CatsxpVPN.PurchasedState.PURCHASED ? (
        <VPNMainWidget
          connectionState={props.catsxpVPNState.connectionState}
          selectedRegion={props.catsxpVPNState.selectedRegion}
        />
      ) : (
        <VPNPromoWidget />
      )}
    </StyledCard>
  )
})

export const VPNWidget = (props: WidgetProps & VPNProps) => {
  const [, saveShowCatsxpVPN] = useNewTabPref('showCatsxpVPN')

  return (
    <VPNWidgetInternal
      {...props}
      hideWidget={() => saveShowCatsxpVPN(false)}
    />
  )
}
