/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

interface Props {
  actions: any
  resource: AdBlock.FilterList
}

export class AdBlockItem extends React.Component<Props, {}> {
  constructor(props: Props) {
    super(props)
  }

  onChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    this.props.actions.enableFilterList(
      this.props.resource.uuid,
      event.target.checked,
    )
  }

  render() {
    return (
      <div>
        <label>
          <input
            id={this.props.resource.uuid}
            type='checkbox'
            checked={this.props.resource.enabled}
            onChange={this.onChange}
          />
          {this.props.resource.title}
        </label>
      </div>
    )
  }
}
