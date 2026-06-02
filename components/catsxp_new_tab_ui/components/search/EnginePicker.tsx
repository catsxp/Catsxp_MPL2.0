/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import Flex from "$web-common/Flex";
import { getLocale } from "$web-common/locale";
import Button from '@catsxp/leo/react/button';
import Floating from '@catsxp/leo/react/floating';
import { color, radius, spacing } from "@catsxp/leo/tokens/css/variables";
import * as React from "react";
import styled, { css } from "styled-components";
import { useSearchContext } from "./SearchContext";
import { MediumSearchEngineIcon } from "./SearchEngineIcon";

const Option = styled.div`
  display: flex;
  align-items: center;
  gap: ${spacing.m};

  padding: ${spacing.m};
  border-radius: ${radius.s};

  &:hover, &[data-selected=true] {
    background: color-mix(in srgb, ${color.text.primary} 10%, transparent 90%);
  }
`

const CustomizeButton = styled(Option)`
  border-top: 1px solid color-mix(in srgb, ${color.text.primary} 10%, transparent 90%);

  justify-content: center;

  &:not(:hover) {
    border-radius: 0;
  }
`

const OpenButton = styled(Button)`
  margin: -6px 0 -6px ${spacing.s};
`

const IconContainer = styled(Flex) <{ open: boolean }>`
  margin-right: 4px;
  border-radius: ${radius.s};
  padding: ${spacing.s};

  width: 32px;
  height: 32px;

  ${p => p.open && css`
    background: color-mix(in srgb, ${color.text.primary} 25%, transparent 75%);
  `}
`

const Menu = styled.div`
  width: 180px;

  background: ${color.container.background};
  border: 1px solid ${color.divider.subtle};

  border-radius: ${radius.m};
  padding: ${spacing.s};

  display: flex;
  flex-direction: column;
  gap: ${spacing.s};
`

const findParentWithTag = (el: HTMLElement | null | undefined, tagName: string) => {
  do {
    el = el?.parentElement
  } while (el && el.tagName !== tagName)

  return el;
}

export default function EnginePicker() {
  const { filteredSearchEngines, searchEngine, setSearchEngine, setOpen: setBoxOpen } = useSearchContext()
  const [open, setOpen] = React.useState(false)

  const buttonRef = React.useRef<HTMLElement>();
  const menuRef = React.useRef<HTMLElement>();

  React.useEffect(() => {
    if (!open) return
    const handler = (e: MouseEvent) => {
      if (!e.composedPath().includes(menuRef.current!)) {
        setOpen(false)
      }
    }

    // Add the handler after we're finished opening the menu, so we don't
    // instantly close it.
    setTimeout(() => document.addEventListener('click', handler))

    return () => {
      document.removeEventListener('click', handler)
    }
  }, [open])

  return <>
    <OpenButton ref={buttonRef} fab kind="plain-faint" slot="anchor-content" onClick={() => setOpen(o => !o)}>
      <IconContainer align="center" justify="center" open={open}>
        <MediumSearchEngineIcon engine={searchEngine} />
      </IconContainer>
    </OpenButton>
    {open && <Floating ref={menuRef} target={findParentWithTag(buttonRef.current, 'LEO-INPUT')!} autoUpdate positionStrategy="fixed" placement="top-start">
      <Menu onClick={e => {
        e.preventDefault()
        e.stopPropagation()
      }}>
        {filteredSearchEngines.map(s => <Option onClick={() => {
          setSearchEngine(s)
          setOpen(false)
        }}
          key={s.keyword}
          data-selected={s === searchEngine}>
          <MediumSearchEngineIcon engine={s} />{s.name}
        </Option>)}
        <CustomizeButton onClick={() => {
          history.pushState(undefined, '', '?openSettings=Search')

          // For now, close the search box - the Settings dialog doesn't use a
          // dialog, so it gets rendered underneath.
          setBoxOpen(false)
          setOpen(false)
        }}>
          {getLocale('searchCustomizeList')}
        </CustomizeButton>
      </Menu>
    </Floating>}
  </>
}
