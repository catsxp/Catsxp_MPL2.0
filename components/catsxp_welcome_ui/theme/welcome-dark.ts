/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import ITheme from 'catsxp-ui/theme/theme-interface'
import IThemeWelcomePage from './welcome-theme'
import defaultTheme from 'catsxp-ui/theme/catsxp-default'
import colors from 'catsxp-ui/theme/colors'

const welcomeDarkTheme: ITheme & IThemeWelcomePage = {
  ...defaultTheme,
  name: 'Welcome Dark',
  color: {
    ...defaultTheme.color,
    text: colors.white,
    panelBackground: colors.grey900,
    outlineColor: 'rgba(255,255,255,0.5)'
  }
}

export default welcomeDarkTheme
