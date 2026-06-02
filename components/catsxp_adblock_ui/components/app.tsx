/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { bindActionCreators, Dispatch } from 'redux'
import { connect } from 'react-redux'

// Components
//import { AdBlockItemList } from './adBlockItemList'
import { CustomSubscriptions } from './customSubscriptions'
//import { CustomFilters } from './customFilters'

// Utils
import * as adblockActions from '../actions/adblock_actions'

interface Props {
  actions: any
  adblockData: AdBlock.State
}

export class AdblockPage extends React.Component<Props, {}> {
  constructor(props: Props) {
    super(props)
  }

  get actions() {
    return this.props.actions
  }

  render() {
    const { actions, adblockData } = this.props
    return (
      <div
        id='adblockPage'
        style={{ margin: '0 auto', maxWidth: '900px' }}
      >
        {/* <AdBlockItemList
          actions={actions}
          resources={adblockData.settings.regionalLists}
        /> */}
        <CustomSubscriptions
          actions={actions}
          subscriptions={adblockData.settings.listSubscriptions}
        />
        {/* <CustomFilters
          actions={actions}
          rules={adblockData.settings.customFilters || ''}
        /> */}
      </div>
    )
  }
}

export const mapStateToProps = (state: AdBlock.ApplicationState) => ({
  adblockData: state.adblockData,
})

export const mapDispatchToProps = (dispatch: Dispatch) => ({
  actions: bindActionCreators(adblockActions, dispatch),
})

export default connect(mapStateToProps, mapDispatchToProps)(AdblockPage)
