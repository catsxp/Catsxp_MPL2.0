/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import * as CatsxpNews from '../../../../../../catsxp_news/browser/resources/shared/api'
import useScrollIntoView from '../../useScrollIntoView'
import { CardImageFromFeedItem } from '../CardImage'
import * as Card from './style'
import useReadArticleClickHandler from '../../useReadArticleClickHandler'
import { OnReadFeedItem } from '../../'

interface Props {
  content: CatsxpNews.FeedItem[]
  publishers: CatsxpNews.Publishers
  categoryName: string
  articleToScrollTo?: CatsxpNews.FeedItemMetadata
  onReadFeedItem: OnReadFeedItem
}

type ListItemProps = {
  item: CatsxpNews.FeedItem
  publisher?: CatsxpNews.Publisher
  onReadFeedItem: OnReadFeedItem
  shouldScrollIntoView: boolean
}

function ListItem (props: ListItemProps) {
  const [cardRef] = useScrollIntoView(props.shouldScrollIntoView)
  const onClick = useReadArticleClickHandler(props.onReadFeedItem, {
    item: props.item
  })
  const data = props.item.article?.data
  if (!data) {
    return null
  }
  return (
    <Card.ListItem>
      <a onClick={onClick} href={data.url.url} ref={cardRef}>
        <Card.Content>
          <Card.Publisher>{props.publisher && props.publisher.publisherName}</Card.Publisher>
          <Card.Heading>{data.title}</Card.Heading>
          <Card.Time>{data.relativeTimeDescription}</Card.Time>
        </Card.Content>
        <Card.ListItemImageFrame>
          <CardImageFromFeedItem list={true} data={data} />
        </Card.ListItemImageFrame>
      </a>
    </Card.ListItem>
  )
}

export default function CategoryGroup (props: Props) {
  // No content no render®
  if (props.content.length < 3 || props.content.some(c => !c.article)) {
    return null
  }
  return (
    <Card.BrandedList>
      <Card.Title>{props.categoryName}</Card.Title>
      <Card.List>
        {
          props.content.map((item, index) => {
            const data = item.article?.data
            // we already validated this, but typescript wants
            // us to do it again
            if (!data) {
              return <React.Fragment key={index} />
            }
            const shouldScrollTo = (
              !!props.articleToScrollTo &&
              props.articleToScrollTo.url.url === data.url.url
            )
            const publisher = props.publishers[data.publisherId]
            return <ListItem
              publisher={publisher}
              item={item}
              key={index}
              shouldScrollIntoView={shouldScrollTo}
              onReadFeedItem={props.onReadFeedItem}
            />
          })
        }
      </Card.List>
    </Card.BrandedList>
  )
}
