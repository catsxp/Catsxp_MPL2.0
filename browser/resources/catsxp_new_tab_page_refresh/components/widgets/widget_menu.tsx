/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Button from '@catsxp/leo/react/button'
import ButtonMenu from '@catsxp/leo/react/buttonMenu'
import Icon from '@catsxp/leo/react/icon'

import { style } from './widget_menu.style'

export function WidgetMenu(props: React.PropsWithChildren) {
  return (
    <div data-css-scope={style.scope}>
      <ButtonMenu placement='bottom-end'>
        <Button
          fab
          kind='plain-faint'
          size='small'
          slot='anchor-content'
        >
          <Icon name='more-vertical' />
        </Button>
        {props.children}
      </ButtonMenu>
    </div>
  )
}
