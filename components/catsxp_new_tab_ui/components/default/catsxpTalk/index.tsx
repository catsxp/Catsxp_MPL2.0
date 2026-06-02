/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import Button from '@catsxp/leo/react/button'
import Icon from '@catsxp/leo/react/icon'

import createWidget from '../widget/index'
import { getLocale } from '../../../../common/locale'

import {
  Content,
  WelcomeText,
  ActionsWrapper,
  CatsxpTalkIcon,
  StyledTitle,
  Privacy,
  PrivacyLink
} from './style'
import { StyledTitleTab, StyledCard } from '../widgetCard'
import { catsxpTalkWidgetUrl } from '../../../constants/new_tab_ui'

interface Props {
  showContent: boolean
  stackPosition: number
  onShowContent: () => void
}

class CatsxpTalk extends React.PureComponent<Props, {}> {
  renderTitle () {
    return (
      <>
        <CatsxpTalkIcon><Icon name='product-catsxp-talk' /></CatsxpTalkIcon>
        {getLocale('catsxpTalkWidgetTitle')}
      </>
    )
  }

  renderTitleTab () {
    return (
      <StyledTitleTab onClick={this.props.onShowContent}>
        {this.renderTitle()}
      </StyledTitleTab>
    )
  }

  shouldCreateCall = () => {
    window.open(catsxpTalkWidgetUrl, '_self', 'noopener')
  }

  render () {
    if (!this.props.showContent) {
      return this.renderTitleTab()
    }

    return (
      <StyledCard>
        <StyledTitle>
          {this.renderTitle()}
        </StyledTitle>
        <Content>
          <WelcomeText>
            {getLocale('catsxpTalkWidgetWelcomeTitle')}
          </WelcomeText>
          <ActionsWrapper>
            <Button onClick={this.shouldCreateCall}>
              {getLocale('catsxpTalkWidgetStartButton')}
            </Button>
            <Privacy>
              <PrivacyLink
                rel='noopener'
                target='_blank'
                href='https://catsxp.com/privacy/browser/#catsxp-talk-learn'
              >
                {getLocale('catsxpTalkWidgetAboutData')}
              </PrivacyLink>
            </Privacy>
          </ActionsWrapper>
        </Content>
      </StyledCard>
    )
  }
}

export const CatsxpTalkWidget = createWidget(CatsxpTalk)
