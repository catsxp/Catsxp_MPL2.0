/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as CatsxpVPN from 'gen/catsxp/components/catsxp_vpn/common/mojom/catsxp_vpn.mojom.m.js'
// Provide access to all the generated types
export * from 'gen/catsxp/components/catsxp_vpn/common/mojom/catsxp_vpn.mojom.m.js'

export default function getVPNServiceHandler () {
  return CatsxpVPN.ServiceHandler.getRemote()
}
