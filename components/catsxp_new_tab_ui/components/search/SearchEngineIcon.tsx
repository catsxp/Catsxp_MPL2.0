/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from "react";
import { icon } from "@catsxp/leo/tokens/css/variables";
import styled from "styled-components";
import { SearchEngineInfo } from "../../api/background";
import Icon from "@catsxp/leo/react/icon";

// Mapping of search engine host to Nala icon for the icons we bundle in the browser
const icons = {
  // The Google search provider has the empty origin :O
  '': 'google-color',
  'duckduckgo.com': 'duckduckgo-color',
  'search.catsxp.com': 'social-catsxp-release-favicon-fullheight-color',
  'www.bing.com': 'bing-color',
  'www.qwant.com': 'qwant-color',
  'www.startpage.com': 'startpage-color',
  'search.yahoo.com': 'yahoo-color',
  'yandex.com': 'yandex-color',
  'ecosia.org': 'ecosia-color',
}

const hide = { opacity: 0 }
// Component which hides the image until it successfully loads (if ever).
export function MaybeImage(props: React.DetailedHTMLProps<React.ImgHTMLAttributes<HTMLImageElement>, HTMLImageElement>) {
  const { src, ...rest } = props
  const [loaded, setLoaded] = React.useState(false)
  const onLoad = React.useCallback(() => setLoaded(true), []);

  React.useEffect(() => {
    setLoaded(false)
  }, [src])
  return <img {...rest} style={loaded ? undefined : hide} onLoad={onLoad} src={`chrome://image?url=${encodeURIComponent(src ?? '')}`} />
}

export function SearchEngineIcon(props: { engine?: SearchEngineInfo, className?: string }) {
  if (!props.engine) return null

  const nalaIcon = icons[props.engine.host as keyof typeof icons]

  return nalaIcon
    ? <Icon name={nalaIcon} className={props.className} />
    : <MaybeImage src={props.engine.faviconUrl.url} className={props.className} />
}

export const MediumSearchEngineIcon = styled(SearchEngineIcon)`
  --leo-icon-size: ${icon.m};

  width: ${icon.m};
  height: ${icon.m};
`
