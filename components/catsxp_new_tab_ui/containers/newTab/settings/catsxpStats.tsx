/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import {
  SettingsRow,
  SettingsText
} from '../../../components/default'
import Toggle from '@catsxp/leo/react/toggle'

import { getLocale } from '../../../../common/locale'
import { useNewTabPref } from '../../../hooks/usePref'

export default function CatsxpStatsSettings () {
  const [showStats, setShowStats] = useNewTabPref('showStats')
  return <div>
    <SettingsRow>
      <SettingsText>{getLocale('showCatsxpStats')}</SettingsText>
      <Toggle
        onChange={() => setShowStats(!showStats)}
        checked={showStats}
        size='small'
      />
    </SettingsRow>
  </div>
}
