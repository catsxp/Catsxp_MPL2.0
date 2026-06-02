/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Button from '@catsxp/leo/react/button'
import getPanelBrowserAPI from '../../api/panel_browser_api'
import { formatLocale, getLocale } from '$web-common/locale'
import {
  Container,
  Title,
  Description,
  Actions,
  StyledAlert,
  ActionsSlotWrapper,
} from './style'
import styles from '../alerts.module.scss'

const handleLearnMoreClick = (e: React.MouseEvent<HTMLAnchorElement>) => {
  e.preventDefault()
  chrome.tabs.create({ url: 'https://www.catsxp.com/hc/en-us/articles/38076796692109', active: true })
}

const onDismissShieldsDisabledAdBlockOnlyModePromptClick = () => {
  getPanelBrowserAPI().dataHandler.setCatsxpShieldsAdBlockOnlyModePromptDismissed()
}

const onDismissRepeatedReloadsAdBlockOnlyModePromptClick = async () => {
  await getPanelBrowserAPI().dataHandler.setCatsxpShieldsAdBlockOnlyModePromptDismissed()
  getPanelBrowserAPI().panelHandler.closeUI()
}

const onEnableAdBlockOnlyModeClick = async (enableShields: boolean) => {
  if (enableShields) {
    await getPanelBrowserAPI().dataHandler.setCatsxpShieldsEnabled(/* isEnabled: */ true)
  }
  await getPanelBrowserAPI().dataHandler.setCatsxpShieldsAdBlockOnlyModeEnabled(/* isEnabled: */ true)
  getPanelBrowserAPI().panelHandler.closeUI()
}

export function AdBlockOnlyModePromptAfterRepeatedReloads() {
  return (
    <Container>
      <Title>
        {getLocale('catsxpShieldsAreYouExperiencingIssuesWithThisSiteTitle')}
      </Title>
      <Description>
        <div>
          {formatLocale(`catsxpShieldsAreYouExperiencingIssuesWithThisSiteDesc1`, {
            $1: content => <a href='https://www.catsxp.com/hc/en-us/articles/38076796692109'
                              onClick={handleLearnMoreClick}>
              {content}
            </a>
          })}
        </div>
        <div>
          {getLocale('catsxpShieldsAreYouExperiencingIssuesWithThisSiteDesc2')}
        </div>
      </Description>
      <Actions>
        <Button
          kind="outline"
          size="medium"
          onClick={onDismissRepeatedReloadsAdBlockOnlyModePromptClick}
        >
          {getLocale('catsxpShieldsDismissAlert')}
        </Button>
        <Button
          size="medium"
          onClick={() => onEnableAdBlockOnlyModeClick(/* enableShields: */ false)}
        >
          {getLocale('catsxpShieldsEnableAdBlockOnlyMode')}
        </Button>
      </Actions>
    </Container>
  );
}

export function AdBlockOnlyModePromptAfterShieldsDisabled() {
  return (
      <StyledAlert type='info' hideIcon>
        <div slot='title'>
          {getLocale('catsxpShieldsAreYouExperiencingIssuesWithThisSiteTitle')}
        </div>
        <div>
          {formatLocale(`catsxpShieldsAreYouExperiencingIssuesWithThisSiteDesc1`, {
            $1: content => <a href='https://www.catsxp.com/hc/en-us/articles/38076796692109'
                              onClick={handleLearnMoreClick}>
              {content}
            </a>
          })}
        </div>
        <div>
          {getLocale('catsxpShieldsAreYouExperiencingIssuesWithThisSiteDesc2')}
        </div>
        <ActionsSlotWrapper slot='actions' className={styles.actionsWrapper}>
          <div className={styles.buttonsWrapper}>
            <Button
              size="medium"
              onClick={() => onEnableAdBlockOnlyModeClick(/* enableShields: */ true)}
            >
              {getLocale('catsxpShieldsEnableAdBlockOnlyMode')}
            </Button>
            <Button
              kind="plain"
              size="medium"
              onClick={() => onDismissShieldsDisabledAdBlockOnlyModePromptClick()}
            >
              {getLocale('catsxpShieldsDismissAlert')}
            </Button>
          </div>
        </ActionsSlotWrapper>
      </StyledAlert>
  )
}
