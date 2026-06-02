/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import ITheme from 'catsxp-ui/theme/theme-interface'
import IThemeWelcomePage from './welcome-theme'
import defaultTheme from 'catsxp-ui/theme/catsxp-default'
import colors from 'catsxp-ui/theme/colors'

const welcomeLightTheme: ITheme & IThemeWelcomePage = {
  ...defaultTheme,
  name: 'Welcome Light',
  color: {
    ...defaultTheme.color,
    text: colors.neutral900,
    panelBackground: '#F9F9FD',
    panelBackgroundSecondary: colors.neutral000,
    outlineColor: 'rgba(255,80,0,0.2)'
  }
}

export default welcomeLightTheme
