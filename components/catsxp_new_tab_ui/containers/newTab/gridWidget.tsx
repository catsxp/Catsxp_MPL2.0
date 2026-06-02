/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { Widget, WidgetProps } from '../../components/default/widget'
import { useNewTabPref } from '../../hooks/usePref'

interface Props extends Omit<WidgetProps, 'hideWidget'> {
    pref: keyof NewTab.Preferences
    container: React.ComponentType<React.PropsWithChildren>
    children: React.ReactNode
}

export default function GridWidget ({ pref: showPref, container: Container, children, ...rest }: Props) {
    const [showing, setShowing] = useNewTabPref(showPref)

    return showing ? <Container>
        <Widget hideWidget={() => setShowing(false)} {...rest}>
        {children}
        </Widget>
    </Container> : null
}
