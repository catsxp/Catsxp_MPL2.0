/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { getLocale } from '$web-common/locale'

import * as S from './style'

import Button from '@catsxp/leo/react/button'

import { WelcomeBrowserProxyImpl } from '../../api/welcome_browser_proxy'

import cubeImg from '../../assets/catsxp-search-cube.svg'
import DataContext from '../../state/context'
import { useViewTypeTransition } from '../../state/hooks'

function HelpWDP () {
  const { viewType, setViewType } = React.useContext(DataContext)

  const { forward } = useViewTypeTransition(viewType)

  const handleAccept = () => {
    WelcomeBrowserProxyImpl.getInstance().enableWebDiscovery()
    setViewType(forward)
  }
  const handleReject = () => {
    setViewType(forward)
  }

  return (
    <S.MainBox>
      <div className='view-header-box'>
        <img
          className='view-logo-box'
          src={cubeImg}
        />
        <h1 className='view-title'>{getLocale('catsxpWelcomeHelpWDPTitle')}</h1>
        <h2 className='view-subtitle'>
          {getLocale('catsxpWelcomeHelpWDPSubtitle')}
        </h2>
      </div>
      <S.BodyBox>
        {getLocale('catsxpWelcomeHelpWDPDescription')}
        <span> </span>
        <a
          href='https://www.catsxp.com/hc/articles/4409406835469-What-is-the-Web-Discovery-Project'
          target='_blank'
        >
          {getLocale('catsxpWelcomeHelpWDPLearnMore')}
        </a>
      </S.BodyBox>
      <S.ActionBox>
        <Button
          kind="filled"
          size="large"
          onClick={handleAccept}
        >
          {getLocale('catsxpWelcomeHelpWDPAccept')}
        </Button>
        <Button
          kind="plain-faint"
          size="large"
          onClick={handleReject}
        >
          {getLocale('catsxpWelcomeHelpWDPReject')}
        </Button>
      </S.ActionBox>
    </S.MainBox>
  )
}

export default HelpWDP
