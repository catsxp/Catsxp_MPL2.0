/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import styled, { css } from 'styled-components'

import Icon from '@catsxp/leo/react/icon'
import Button from '@catsxp/leo/react/button'
import ButtonMenu from '@catsxp/leo/react/buttonMenu'
import { color, spacing } from '@catsxp/leo/tokens/css/variables'

interface MenuItemProps {
  name: string
  iconName: string
  onClick: () => void
}

interface MenuProps {
  items: Array<MenuItemProps | undefined>
  visible: boolean
  onShowMenu?: () => void
  onDismissMenu?: () => void
}

const StyledRow = styled.div`
  display: flex;
  justify-content: space-between;
  align-items: center;
  gap: ${spacing.m};
`

const StyledButtonMenu = styled(ButtonMenu)<{ visible: boolean }>`
  ${(p) =>
    !p.visible &&
    css`
      visibility: hidden;
    `}
  --leo-icon-size: 20px;
  color: ${color.text.secondary};
`

const StyledButton = styled(Button)`
  --leo-button-padding: 0;
`

export default function ContextualMenuAnchorButton ({
  items,
  visible,
  onShowMenu,
  onDismissMenu
}: MenuProps) {
  const [open, setOpen] = React.useState(false)

  // When the anchor button isn't visible, hide the menu
  React.useEffect(() => {
    if (!visible) setOpen(false)
  }, [visible])

  return (
    <div onClick={(e) => e.stopPropagation()}>
      <StyledButtonMenu
        visible={visible}
        onChange={({ isOpen }) => {
          if (isOpen) onShowMenu?.()
          setOpen(isOpen)
        }}
        onClose={() => onDismissMenu?.()}
        isOpen={open}
      >
        <StyledButton kind='plain-faint' size='small' slot='anchor-content'>
          <Icon name='more-horizontal' />
        </StyledButton>
        {items
          .filter((i) => i)
          .map((i) => (
            <leo-menu-item
              key={i!.name}
              onClick={(e) => {
                i!.onClick()
              }}
            >
              <StyledRow>
                <span>{i!.name}</span>
                <Icon name={i!.iconName} />
              </StyledRow>
            </leo-menu-item>
          ))}
      </StyledButtonMenu>
    </div>
  )
}
