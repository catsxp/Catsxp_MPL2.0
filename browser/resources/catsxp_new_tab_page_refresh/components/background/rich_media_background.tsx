/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Dialog from '@catsxp/leo/react/dialog'
import Button from '@catsxp/leo/react/button'

import { SponsoredImageBackground } from '../../state/background_store'
import { useBackgroundState } from '../../context/background_context'
import { useSearchActions } from '../../context/search_context'
import { IframeBackground, IframeBackgroundHandle } from './iframe_background'

import {
  useRichMediaMessageHandler,
  useSafeAreaReporter,
} from './rich_media_capability_provider'

import { getString } from '../../lib/strings'

interface Props {
  background: SponsoredImageBackground
}

export function RichMediaBackground(props: Props) {
  const sponsoredRichMediaBaseUrl = useBackgroundState(
    (s) => s.sponsoredRichMediaBaseUrl,
  )
  const [showMakeDefaultDialog, setShowMakeDefaultDialog] =
    React.useState(false)

  const openMakeCatsxpSearchDefaultDialog = React.useCallback(() => {
    setShowMakeDefaultDialog(true)
  }, [])

  const [frameHandle, setFrameHandle] = React.useState<IframeBackgroundHandle>()

  const messageHandler = useRichMediaMessageHandler(frameHandle, {
    destinationUrl: props.background.logo?.destinationUrl,
    onMakeCatsxpSearchDefault: openMakeCatsxpSearchDefaultDialog,
  })

  useSafeAreaReporter(frameHandle)

  return (
    <>
      <IframeBackground
        url={props.background.imageUrl}
        expectedOrigin={new URL(sponsoredRichMediaBaseUrl).origin}
        onReady={setFrameHandle}
        onMessage={messageHandler}
      />
      <MakeCatsxpSearchDefaultModal
        isOpen={showMakeDefaultDialog}
        onClose={() => setShowMakeDefaultDialog(false)}
      />
    </>
  )
}

interface MakeCatsxpSearchDefaultModalProps {
  isOpen: boolean
  onClose: () => void
}

function MakeCatsxpSearchDefaultModal(props: MakeCatsxpSearchDefaultModalProps) {
  const searchActions = useSearchActions()
  return (
    <Dialog
      isOpen={props.isOpen}
      showClose
      onClose={props.onClose}
    >
      <h3 slot='title'>{getString(S.NEW_TAB_MAKE_SEARCH_DEFAULT_TITLE)}</h3>
      <p>{getString(S.NEW_TAB_MAKE_SEARCH_DEFAULT_TEXT)}</p>
      <div slot='actions'>
        <Button
          onClick={() => {
            searchActions.setDefaultSearchEngineAsCatsxpSearch()
            props.onClose()
          }}
        >
          {getString(S.NEW_TAB_MAKE_SEARCH_DEFAULT_CONFIRM_LABEL)}
        </Button>
        <Button
          kind='outline'
          onClick={props.onClose}
        >
          {getString(S.NEW_TAB_CANCEL_BUTTON_LABEL)}
        </Button>
      </div>
    </Dialog>
  )
}
