/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import {
  FeaturedSettingsWidget,
  StyledBannerImage,
  StyledSettingsInfo,
  StyledSettingsTitle,
  StyledSettingsCopy,
  SettingsWidget,
  StyledWidgetSettings,
  ToggleCardsWrapper,
  ToggleCardsTitle,
  ToggleCardsCopy,
  ToggleCardsSwitch,
  ToggleCardsText
} from '../../../components/default'
import catsxpTalkBanner from './assets/catsxp-talk.png'
import catsxpVPNBanner from './assets/catsxp-vpn.png'
import rewardsBanner from './assets/catsxprewards.png'
import Toggle from '@catsxp/leo/react/toggle'
import Button from '@catsxp/leo/react/button'

import { getLocale } from '$web-common/locale'
import { loadTimeData } from '$web-common/loadTimeData'
import Icon from '@catsxp/leo/react/icon'
import styled, { css } from 'styled-components'
import { spacing } from '@catsxp/leo/tokens/css/variables'
import { useNewTabPref } from '../../../hooks/usePref'

const StyledButton = styled(Button) <{ float: boolean }>`
  margin-top: ${spacing.xl};
  width: fit-content;
  ${p => p.float && css`
    float: right;
    margin-right: ${spacing.m};
  `}
`

interface Props {
  toggleShowCatsxpTalk: () => void
  showCatsxpTalk: boolean
  catsxpTalkSupported: boolean
  toggleShowRewards: () => void
  showRewards: boolean
  catsxpRewardsSupported: boolean
  toggleCards: (show: boolean) => void
  cardsHidden: boolean
}

const ToggleButton = ({ on, toggleFunc, float }: { on: boolean, toggleFunc: any, float?: boolean }) => {
  return <StyledButton onClick={toggleFunc} kind={on ? 'outline' : 'filled'} float={!!float}>
    <div slot="icon-before">
      <Icon name={on ? 'eye-off' : 'plus-add'} />
    </div>
    {getLocale(on ? 'hideWidget' : 'addWidget')}
  </StyledButton>
}

function CardSettings({ toggleShowCatsxpTalk, showCatsxpTalk, catsxpTalkSupported, toggleShowRewards, showRewards, catsxpRewardsSupported, toggleCards, cardsHidden }: Props) {
  const [showCatsxpVPN, saveShowCatsxpVPN] = useNewTabPref('showCatsxpVPN')
  const [isCatsxpTalkDisabledByPolicy] = useNewTabPref(
    'isCatsxpTalkDisabledByPolicy'
  )

  return <StyledWidgetSettings>
    {catsxpTalkSupported && !isCatsxpTalkDisabledByPolicy &&
      <FeaturedSettingsWidget>
      <StyledBannerImage src={catsxpTalkBanner} />
      <StyledSettingsInfo>
        <StyledSettingsTitle>
          {getLocale('catsxpTalkWidgetTitle')}
        </StyledSettingsTitle>
        <StyledSettingsCopy>
          {getLocale('catsxpTalkWidgetWelcomeTitle')}
        </StyledSettingsCopy>
      </StyledSettingsInfo>
      <ToggleButton on={showCatsxpTalk} toggleFunc={toggleShowCatsxpTalk} float />
    </FeaturedSettingsWidget>}
    {catsxpRewardsSupported && <SettingsWidget>
      <StyledBannerImage src={rewardsBanner} />
      <StyledSettingsInfo>
        <StyledSettingsTitle>
          {getLocale('catsxpRewardsTitle')}
        </StyledSettingsTitle>
        <StyledSettingsCopy>
          {getLocale('rewardsWidgetDesc')}
        </StyledSettingsCopy>
      </StyledSettingsInfo>
      <ToggleButton on={showRewards} toggleFunc={toggleShowRewards} />
    </SettingsWidget>}
    {loadTimeData.getBoolean('vpnWidgetSupported') && <SettingsWidget>
      <StyledBannerImage src={catsxpVPNBanner} />
      <StyledSettingsInfo>
        <StyledSettingsTitle>
          {getLocale('catsxpVpnWidgetSettingTitle')}
        </StyledSettingsTitle>
        <StyledSettingsCopy>
          {getLocale('catsxpVpnWidgetSettingDesc')}
        </StyledSettingsCopy>
      </StyledSettingsInfo>
      <ToggleButton on={showCatsxpVPN!} toggleFunc={() => saveShowCatsxpVPN(!showCatsxpVPN)} />
    </SettingsWidget>}
    <FeaturedSettingsWidget>
      <ToggleCardsWrapper>
        <ToggleCardsText>
          <ToggleCardsTitle>
            {getLocale('cardsToggleTitle')}
          </ToggleCardsTitle>
          <ToggleCardsCopy>
            {getLocale('cardsToggleDesc')}
          </ToggleCardsCopy>
        </ToggleCardsText>
        <ToggleCardsSwitch>
          <Toggle
            size='small'
            onChange={() => toggleCards(cardsHidden)}
            checked={!cardsHidden}
          />
        </ToggleCardsSwitch>
      </ToggleCardsWrapper>
    </FeaturedSettingsWidget>
  </StyledWidgetSettings>
}

export default React.memo(CardSettings)
