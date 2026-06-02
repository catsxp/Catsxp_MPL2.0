/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

export enum ViewType {
  ScriptsList,
  FingerprintList,
  AdsList,
  HttpsList,
  Main
}

export type PermissionButtonHandler = ((name: string) => void)
