/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

/* global loadTimeDataRaw */

import {
  SecurityInterstitialCommandId,
  sendCommand,
} from 'chrome://interstitials/common/resources/interstitial_common.js'

function setupEvents() {
  const primaryButton = document.querySelector('#primary-button')
  primaryButton.addEventListener('click', function () {
    sendCommand(SecurityInterstitialCommandId.CMD_PROCEED)
  })

  const backButton = document.querySelector('#back-button')
  backButton.addEventListener('click', function () {
    sendCommand(SecurityInterstitialCommandId.CMD_DONT_PROCEED)
  })

  const dontWarnAgainCheckbox = document.querySelector(
    '#dont-warn-again-checkbox',
  )
  dontWarnAgainCheckbox.addEventListener('click', function () {
    sendCommand(
      dontWarnAgainCheckbox.checked
        ? SecurityInterstitialCommandId.CMD_DO_REPORT
        : SecurityInterstitialCommandId.CMD_DONT_REPORT,
    )
  })

  // Check if we should hide the "Don't warn again" div.
  // We hide this in private browsing, because the checkbox
  // adds a custom exception rule.
  const showCheckbox = loadTimeDataRaw.showDontWarnAgainCheckbox
  if (showCheckbox) {
    const dontWarnAgainDiv = document.querySelector('#dont-warn-again')
    dontWarnAgainDiv.classList.remove('hidden')
  }
}

document.addEventListener('DOMContentLoaded', setupEvents)
