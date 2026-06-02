/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

const backgroundFills = ['#DFE1E5',
'#B7DEFF', '#F5C5E2', '#CCC5F5', '#C5F5DB', '#E9F5C5']

const AvatarIcon = (props: any) => {
  const bgFill = React.useMemo(() => {
    return backgroundFills[Math.round(Math.random() * (backgroundFills.length - 1))]
  }, [])

  return (
    <svg
      viewBox="0 0 48 48"
      fill="none"
      xmlns="http://www.w3.org/2000/svg"
      {...props}
    >
      <circle cx={24} cy={24} r={24} fill={bgFill} />
      <ellipse cx={24} cy={33} rx={11} ry={7} fill="#5F6372" />
      <circle cx={24} cy={19} r={5} fill="#5F6372" />
    </svg>
  )
}

export default AvatarIcon
