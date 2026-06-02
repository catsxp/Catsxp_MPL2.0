/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { DragOverlay, useDndContext } from '@dnd-kit/core'
import * as React from 'react'
import { SiteTile } from './gridTile'

export function TopSiteDragOverlay (props: { sites: NewTab.Site[] }) {
    const { active } = useDndContext()
    const dragging = active && props.sites.find(s => s.id === active.id)
    return <DragOverlay>
      {dragging && <SiteTile site={dragging}/>}
    </DragOverlay>
  }
