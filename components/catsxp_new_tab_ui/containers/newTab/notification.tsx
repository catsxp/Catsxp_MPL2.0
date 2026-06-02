/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import Icon from '@catsxp/leo/react/icon'

// Feature-specific components
import {
  SiteRemovalNotification,
  SiteRemovalAction,
  SiteRemovalText
} from '../../components/default'

// Utils
import { getLocale } from '../../../common/locale'

// Types
import * as newTabActions from '../../actions/new_tab_actions'
import * as gridSitesActions from '../../actions/grid_sites_actions'

interface Props {
  actions: typeof newTabActions & typeof gridSitesActions
  showRestoreAll: boolean
}

export default class Notification extends React.Component<Props, {}> {
  componentDidMount () {
    // After 3s, auto-close this notification
    window.setTimeout(() => this.onHideSiteRemovalNotification(), 3000)
  }

  onUndoRemoveTopSite = () => {
    this.props.actions.undoRemoveTile()
  }

  onUndoRemoveAllTopSites = () => {
    this.props.actions.restoreDefaultTiles()
  }

  onHideSiteRemovalNotification = () => {
    this.props.actions.showTilesRemovedNotice(false)
  }

  render () {
    return (
       <SiteRemovalNotification>
          <SiteRemovalText>{getLocale('thumbRemoved')}</SiteRemovalText>
          <SiteRemovalAction
            onClick={this.onUndoRemoveTopSite}
          >
            {getLocale('undoRemoved')}
          </SiteRemovalAction>
          { this.props.showRestoreAll
            ? <SiteRemovalAction onClick={this.onUndoRemoveAllTopSites}>
              {getLocale('restoreAll')}
            </SiteRemovalAction>
            : null
          }
          <SiteRemovalAction
            onClick={this.onHideSiteRemovalNotification}
            iconOnly={true}
            title={getLocale('close')}
          >
            <Icon name='close' />
          </SiteRemovalAction>
       </SiteRemovalNotification>
    )
  }
}
