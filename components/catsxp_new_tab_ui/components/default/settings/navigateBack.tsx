/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { getLocale } from '$web-common/locale'
import Icon from '@catsxp/leo/react/icon'
import Button from '@catsxp/leo/react/button'

type Props = {
  onBack: () => any
  title?: string
}

export default function NavigateBack(props: Props) {
  return <Button onClick={props.onBack} kind='plain-faint' fab size='tiny'>
    <Icon name='arrow-left' slot='icon-before' />
    <span>{props.title ? props.title : getLocale('settingsNavigateBack')}</span>
  </Button>
}
