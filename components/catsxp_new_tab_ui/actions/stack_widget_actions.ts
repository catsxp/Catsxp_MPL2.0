/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { action } from 'typesafe-actions'

// Constants
import { types } from '../constants/stack_widget_types'

export const setForegroundStackWidget = (widget: NewTab.StackWidget) => action(types.SET_FOREGROUND_STACK_WIDGET, {
  widget
})

export const saveWidgetStackOrder = () => action(types.SAVE_WIDGET_STACK_ORDER)
