/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import styled, * as Styled from 'styled-components'
import ICatsxpTheme from 'catsxp-ui/theme/theme-interface'
import IWelcomeTheme from './welcome-theme'

type Theme = ICatsxpTheme & IWelcomeTheme

export default styled as unknown as Styled.ThemedStyledInterface<Theme>
export const css = Styled.css as Styled.ThemedCssFunction<Theme>
