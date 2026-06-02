/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { getLocale } from '../../common/locale'

interface Props {
  actions: any
  rules: string
}

export class CustomFilters extends React.Component<Props, {}> {
  constructor(props: Props) {
    super(props)
  }

  onChangeCustomFilters = (event: React.ChangeEvent<HTMLTextAreaElement>) => {
    this.props.actions.updateCustomFilters(event.target.value)
  }

  render() {
    return (
      <div>
        <div style={{ fontSize: '18px', marginTop: '20px' }}>
          {getLocale('customFiltersTitle')}
        </div>
        <div style={{ fontWeight: 'bold' }}>
          {getLocale('customFiltersInstructions')}
        </div>
        <textarea
          style={{ marginTop: '10px' }}
          data-testid={'customFiltersInput'}
          cols={100}
          rows={10}
          spellCheck={false}
          value={this.props.rules}
          onChange={this.onChangeCustomFilters}
        />
      </div>
    )
  }
}
