/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import * as CatsxpNews from '../../../../../../catsxp_news/browser/resources/shared/api'
import { CardImageFromFeedItem } from '../CardImage'
import * as Card from '../../cardSizes'
import PublisherMeta from '../PublisherMeta'
import useScrollIntoView from '../../useScrollIntoView'
import useReadArticleClickHandler from '../../useReadArticleClickHandler'
import { OnReadFeedItem, OnSetPublisherPref } from '../../'
// TODO(petemill): Large and Medium article should be combined to 1 component.

interface Props {
  content: CatsxpNews.FeedItem[]
  publishers: CatsxpNews.Publishers
  articleToScrollTo?: CatsxpNews.FeedItemMetadata
  onReadFeedItem: OnReadFeedItem
  onSetPublisherPref: OnSetPublisherPref
}

type ArticleProps = {
  item: CatsxpNews.FeedItem
  publisher?: CatsxpNews.Publisher
  shouldScrollIntoView?: boolean
  onReadFeedItem: OnReadFeedItem
  onSetPublisherPref: OnSetPublisherPref
}

function MediumArticle (props: ArticleProps) {
  const { publisher, item } = props
  const [cardRef] = useScrollIntoView(props.shouldScrollIntoView || false)
  const onClick = useReadArticleClickHandler(props.onReadFeedItem, {
    item
  })
  const data = item.article?.data
  if (!data) {
    return null
  }
  return (
    <Card.Small data-score={data.score}>
      <a onClick={onClick} href={data.url.url} ref={cardRef}>
        <CardImageFromFeedItem
          data={data}
        />
        <Card.Content>
          <Card.Text>
            {data.title}
          <Card.Time>{data.relativeTimeDescription}</Card.Time>
          {
            publisher &&
              <Card.Publisher>
                <PublisherMeta
                  publisher={publisher}
                  onSetPublisherPref={props.onSetPublisherPref}
                />
              </Card.Publisher>
          }
          </Card.Text>
        </Card.Content>
      </a>
    </Card.Small>
  )
}

export default function CardSingleArticleMedium (props: Props) {
  const { content }: Props = props

  // no full content no render®
  if (content.length !== 2) {
    return null
  }

  return (
    <Card.ContainerForTwo>
      {
        content.map((item, index) => {
          const data = item.article?.data
          if (!data) {
            return (
              <React.Fragment key={index} />
            )
          }
          const shouldScrollIntoView = props.articleToScrollTo && (props.articleToScrollTo.url.url === data.url.url)
          const publisher = props.publishers[data.publisherId]
          return (
            <MediumArticle
              key={index}
              publisher={publisher}
              item={item}
              onReadFeedItem={props.onReadFeedItem}
              onSetPublisherPref={props.onSetPublisherPref}
              shouldScrollIntoView={shouldScrollIntoView}
            />
          )
        })
      }
    </Card.ContainerForTwo>
  )
}
