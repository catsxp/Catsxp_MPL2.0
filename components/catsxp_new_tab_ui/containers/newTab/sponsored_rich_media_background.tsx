/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import styled from 'styled-components'
import { loadTimeData } from '$web-common/loadTimeData'
import * as CatsxpAds from 'gen/catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.m.js'

export interface SponsoredRichMediaBackgroundInfo {
  url: string
  placementId: string
  creativeInstanceId: string
  metricType: CatsxpAds.NewTabPageAdMetricType
  targetUrl: string
}

interface StatusProps {
  richMediaHasLoaded: boolean
}

interface Props extends StatusProps {
  sponsoredRichMediaBackgroundInfo: SponsoredRichMediaBackgroundInfo
  onEventReported: (name: CatsxpAds.NewTabPageAdEventType) => void
  onLoaded: () => void
}

const iframeAllow = `
  accelerometer 'none';
  ambient-light-sensor 'none';
  camera 'none';
  display-capture 'none';
  document-domain 'none';
  fullscreen 'none';
  geolocation 'none';
  gyroscope 'none';
  magnetometer 'none';
  microphone 'none';
  midi 'none';
  payment 'none';
  publickey-credentials-get 'none';
  usb 'none'
`.trim().replace(/\n/g, '')

const SponsoredRichMediaBackgroundIframe = styled('iframe') <StatusProps>`
  opacity: ${p => p.richMediaHasLoaded ? 1 : 0};
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  border: none;
  z-index: 0;

  /* Blur out the content when Catsxp News is interacted
     with. We need the opacity to fade out our background image.
   */
  filter: blur(calc(var(--ntp-extra-content-effect-multiplier, 0) * 38px));
  opacity: max(0.3, calc(1 - var(--ntp-extra-content-effect-multiplier)));
  background: var(--default-bg-color);
`

/// We expect the event data to be of the following format:
/// {
///   type: 'richMediaEvent',
///   value: 'click'
/// }
function getEventType(event: MessageEvent): CatsxpAds.NewTabPageAdEventType | undefined {
  if (!event.data || event.data.type !== 'richMediaEvent') {
    return undefined
  }

  const eventMap: { [key: string]: CatsxpAds.NewTabPageAdEventType } = {
    'click': CatsxpAds.NewTabPageAdEventType.kClicked,
    'interaction': CatsxpAds.NewTabPageAdEventType.kInteraction,
    'mediaPlay': CatsxpAds.NewTabPageAdEventType.kMediaPlay,
    'media25': CatsxpAds.NewTabPageAdEventType.kMedia25,
    'media100': CatsxpAds.NewTabPageAdEventType.kMedia100
  }

  return eventMap[event.data.value]
}

export function SponsoredRichMediaBackground(props: Props) {
  const iframeRef = React.useRef<HTMLIFrameElement | null>(null)
  const { sponsoredRichMediaBackgroundInfo } = props

  React.useEffect(() => {
    try {
      const ntpNewTabTakeoverRichMediaUrlOrigin =
        new URL(loadTimeData.getString('ntpNewTabTakeoverRichMediaUrl')).origin

      const listener = (event: MessageEvent) => {
        if (event.origin !== ntpNewTabTakeoverRichMediaUrlOrigin) {
          return
        }

        if (!iframeRef.current) {
          return
        }

        const { contentWindow } = iframeRef.current
        if (!event.source || event.source !== contentWindow || !event.data) {
          return
        }

        const eventType = getEventType(event)
        if (!eventType) {
          return
        }

        props.onEventReported(eventType)
      }

      window.addEventListener('message', listener)
      return () => { window.removeEventListener('message', listener) }
    } catch (e) {
      console.error('Error setting up sponsored rich media event listener')
      return () => { }
    }
  }, [props.onEventReported])

  return (
    <SponsoredRichMediaBackgroundIframe
      ref={iframeRef}
      richMediaHasLoaded={props.richMediaHasLoaded}
      allow={iframeAllow}
      src={sponsoredRichMediaBackgroundInfo.url}
      sandbox='allow-scripts allow-same-origin'
      onLoad={props.onLoaded}>
    </SponsoredRichMediaBackgroundIframe>
  )
}
