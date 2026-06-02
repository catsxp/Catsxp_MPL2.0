/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import * as Card from '../cardSizes'
import * as CatsxpNews from '../../../../../catsxp_news/browser/resources/shared/api'

type Props = {
  imageUrl?: string
  list?: boolean
  onLoaded?: () => any
}

export default function CardImage(props: Props) {
  const imageUrl = `chrome://image?url=${encodeURIComponent(props.imageUrl ?? '')}`
  const [isImageLoaded, setIsImageLoaded] = React.useState(false)
  React.useEffect(() => {
    if (imageUrl) {
      const img = new Image()
      let shouldCancel = false
      img.addEventListener('load', () => {
        if (!shouldCancel) {
          setIsImageLoaded(true)
          props.onLoaded?.()
        }
      })
      img.src = imageUrl
      return () => { shouldCancel = true }
    }

    return () => { }
  }, [imageUrl])
  const Frame = props.list ? Card.ListImageFrame : Card.ImageFrame
  return (
    <Frame data-source={props.imageUrl} isImageLoaded={isImageLoaded}>
      <Card.Image src={imageUrl} />
    </Frame>
  )
}

type FromFeedItemProps = Omit<Props, 'imageUrl' | 'isUnpadded'> & {
  data: CatsxpNews.FeedItemMetadata
}

export function CardImageFromFeedItem(props: FromFeedItemProps) {
  React.useEffect(() => {
    if (!props.data.image.imageUrl && !props.data.image.paddedImageUrl) {
      // Shouldn't happen since backend filters out items
      // with no image.
      // It can happen for direct-feed items, and we just don't display the
      // image.
      // This is in a useEffect so it does not log every render.
      console.warn('Catsxp News found item with no image', props.data.url.url)
    }
  }, [props.data.image.imageUrl, props.data.image.paddedImageUrl])
  const imageUrl = React.useMemo(() => {
    if (props.data.image.imageUrl?.url) { return props.data.image.imageUrl.url }
    if (props.data.image.paddedImageUrl?.url) { return props.data.image.paddedImageUrl.url }
    return ''
  }, [props.data.image.imageUrl, props.data.image.paddedImageUrl, props.data.description])
  const { data, ...baseProps } = props
  if (imageUrl) {
    return (
      <CardImage
        {...baseProps}
        imageUrl={imageUrl}
      />
    )
  }
  return null
}
