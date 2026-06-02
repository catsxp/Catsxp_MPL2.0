/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Icon from '@catsxp/leo/react/icon'
import ProgressRing from '@catsxp/leo/react/progressRing'
import Toggle from '@catsxp/leo/react/toggle'

import {
  useBackgroundState,
  useBackgroundActions,
} from '../../context/background_context'
import { getString } from '../../lib/strings'
import { inlineCSSVars } from '../../lib/inline_css_vars'
import { BackgroundTypePanel } from './background_type_panel'

import {
  SelectedBackgroundType,
  backgroundCSSValue,
  gradientPreviewBackground,
  solidPreviewBackground,
} from '../../state/background_store'

import { style } from './background_panel.style'

export function BackgroundPanel() {
  const actions = useBackgroundActions()

  const backgroundsEnabled = useBackgroundState((s) => s.backgroundsEnabled)
  const backgroundsCustomizable = useBackgroundState(
    (s) => s.backgroundsCustomizable,
  )
  const selectedBackground = useBackgroundState((s) => s.selectedBackground)
  const catsxpBackgrounds = useBackgroundState((s) => s.catsxpBackgrounds)
  const customBackgrounds = useBackgroundState((s) => s.customBackgrounds)

  const [panelType, setPanelType] =
    React.useState<SelectedBackgroundType | null>(null)
  const [uploading, setUploading] = React.useState(false)

  React.useEffect(() => {
    setUploading(false)
  }, [selectedBackground, customBackgrounds])

  function setPanel(type?: SelectedBackgroundType) {
    setPanelType(type ?? null)
  }

  function getTypePreviewValue(type: SelectedBackgroundType) {
    const isSelectedType = type === selectedBackground.type
    switch (type) {
      case SelectedBackgroundType.kCatsxp:
        return catsxpBackgrounds[0]?.imageUrl ?? ''
      case SelectedBackgroundType.kCustom:
        if (isSelectedType && selectedBackground.value) {
          return selectedBackground.value
        }
        return customBackgrounds[0] ?? ''
      case SelectedBackgroundType.kSolid:
        if (isSelectedType && selectedBackground.value) {
          return selectedBackground.value
        }
        return solidPreviewBackground
      case SelectedBackgroundType.kGradient:
        if (isSelectedType && selectedBackground.value) {
          return selectedBackground.value
        }
        return gradientPreviewBackground
      default:
        console.error('Unhandled background type', type)
        return ''
    }
  }

  function renderUploadPreview() {
    return (
      <div className='preview upload'>
        {uploading ? <ProgressRing /> : <Icon name='upload' />}
        {getString(S.NEW_TAB_UPLOAD_BACKGROUND_LABEL)}
      </div>
    )
  }

  function renderTypePreview(type: SelectedBackgroundType) {
    if (type === SelectedBackgroundType.kCustom &&
        customBackgrounds.length === 0) {
      return renderUploadPreview()
    }
    return (
      <div
        className='preview'
        style={inlineCSSVars({
          '--preview-background':
            backgroundCSSValue(type, getTypePreviewValue(type))
        })}
      >
        {
          type === selectedBackground.type &&
            <span className='selected-marker'>
              <Icon name='check-normal' />
            </span>
        }
      </div>
    )
  }

  function showCustomBackgroundChooser() {
    actions.showCustomBackgroundChooser().then((backgroundSelected) => {
      if (backgroundSelected) {
        setUploading(true)
      }
    })
  }

  function onCustomPreviewClick() {
    if (customBackgrounds.length === 0) {
      showCustomBackgroundChooser()
    } else {
      setPanel(SelectedBackgroundType.kCustom)
    }
  }

  if (panelType !== null) {
    return (
      <div data-css-scope={style.scope}>
        <BackgroundTypePanel
          backgroundType={panelType}
          renderUploadOption={() => (
            <button onClick={showCustomBackgroundChooser}>
              {renderUploadPreview()}
            </button>
          )}
          onClose={() => setPanel()}
        />
      </div>
    )
  }

  return (
    <div data-css-scope={style.scope}>
      <Toggle
        className='toggle-row'
        size='small'
        checked={backgroundsEnabled}
        onChange={({ checked }) => {
          actions.setBackgroundsEnabled(checked)
        }}
      >
        <span className='label'>
          {getString(S.NEW_TAB_SHOW_BACKGROUNDS_LABEL)}
        </span>
      </Toggle>
      {backgroundsEnabled && backgroundsCustomizable && (
        <>
          <div className='background-options'>
            <div className='background-option'>
              <button onClick={onCustomPreviewClick}>
                {renderTypePreview(SelectedBackgroundType.kCustom)}
                {getString(S.NEW_TAB_CUSTOM_BACKGROUND_LABEL)}
              </button>
            </div>
            <div className='background-option'>
              <button
                onClick={() => {
                  actions.selectBackground(SelectedBackgroundType.kCatsxp, '')
                }}
              >
                {renderTypePreview(SelectedBackgroundType.kCatsxp)}
                {getString(S.NEW_TAB_CATSXP_BACKGROUND_LABEL)}
              </button>
            </div>
            <div className='background-option'>
              <button onClick={() => setPanel(SelectedBackgroundType.kSolid)}>
                {renderTypePreview(SelectedBackgroundType.kSolid)}
                {getString(S.NEW_TAB_SOLID_BACKGROUND_LABEL)}
              </button>
            </div>
            <div className='background-option'>
              <button
                onClick={() => setPanel(SelectedBackgroundType.kGradient)}
              >
                {renderTypePreview(SelectedBackgroundType.kGradient)}
                {getString(S.NEW_TAB_GRADIENT_BACKGROUND_LABEL)}
              </button>
            </div>
          </div>
        </>
      )}
    </div>
  )
}
