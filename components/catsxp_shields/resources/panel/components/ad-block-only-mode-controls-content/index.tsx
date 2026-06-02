/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Alert from '@catsxp/leo/react/alert'
import Button from '@catsxp/leo/react/button'
import Icon, { setIconBasePath } from '@catsxp/leo/react/icon'
import getPanelBrowserAPI from '../../api/panel_browser_api'
import { getLocale } from '$web-common/locale'
import { GlobalSettings } from "../advanced-controls-content"
import {
  Container,
  HeaderRow,
  HeaderTextColumn,
  HeaderTitle,
  HeaderDescription,
} from './style'
import styles from '../alerts.module.scss'

setIconBasePath('chrome://resources/catsxp-icons')

const onSettingsClick = () => {
  chrome.tabs.create({ url: 'chrome://settings/shields', active: true })
}

function IsTheSiteWorkingCorrectlyNowAdBlockOnlyModeNotice(
  { isCatsxpShieldsEnabled }: { isCatsxpShieldsEnabled: boolean }) {
  const onLooksGoodClick = () => {
    getPanelBrowserAPI().panelHandler.closeUI()
  }

  const onReportClick = () => {
    getPanelBrowserAPI().dataHandler.openWebCompatWindow()
  }

  return (
    <Container>
      <HeaderRow>
        <HeaderTextColumn>
          <HeaderTitle>
            {getLocale('catsxpShieldsAdBlockOnlyModeEnabledTitle')}
          </HeaderTitle>
          <HeaderDescription>
            {getLocale('catsxpShieldsAdBlockOnlyModeEnabledDesc')}
          </HeaderDescription>
        </HeaderTextColumn>
        <Button
          kind='plain-faint'
          size='small'
          onClick={onSettingsClick}
        >
          <Icon name='launch' />
        </Button>
      </HeaderRow>
      <Alert type='info' hideIcon>
        <div slot='title'>
          {getLocale('catsxpShieldsIsThisSiteWorkingCorrectlyNowTitle')}
        </div>
        <div>
          {getLocale('catsxpShieldsIsThisSiteWorkingCorrectlyNowDesc')}
        </div>
        <div slot='actions' className={styles.actionsWrapper}>
          {isCatsxpShieldsEnabled ? (
            <div className={styles.buttonsWrapper}>
              <Button size="medium" onClick={onLooksGoodClick}>
                {getLocale('catsxpShieldsIsThisSiteWorkingCorrectlyNowLooksGood')}
              </Button>
              <Button kind="plain" size="medium" onClick={onReportClick}>
                {getLocale('catsxpShieldsIsThisSiteWorkingCorrectlyNowReportSite')}
              </Button>
            </div>
          ) : (
            <Button size="medium" onClick={onReportClick}>
              {getLocale('catsxpShieldsIsThisSiteWorkingCorrectlyNowReportSite')}
            </Button>
          )}
        </div>
      </Alert>
    </Container>
  )
}

function AdBlockOnlyModeControlsContent(
    { isCatsxpShieldsEnabled }: { isCatsxpShieldsEnabled: boolean }) {
  return (
    <section id='global-controls-content'>
      <IsTheSiteWorkingCorrectlyNowAdBlockOnlyModeNotice
        isCatsxpShieldsEnabled={isCatsxpShieldsEnabled} />
      {isCatsxpShieldsEnabled && <GlobalSettings showAdblockLists={false} />}
    </section>
  )
}

export default AdBlockOnlyModeControlsContent
