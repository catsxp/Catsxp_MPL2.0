/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_MIME_UTIL_H_
#define CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_MIME_UTIL_H_

#include <optional>
#include <string>
#include <vector>

#include "base/files/file_path.h"

// Utilities for Mime <-> File extension conversion.
// These have more broader coverage than "net/base/mime_util.h" has as for the
// media types.
namespace playlist::mime_util {

std::optional<base::FilePath::StringType> GetFileExtensionForMimetype(
    std::string_view mime_type);

std::optional<std::string> GetMimeTypeForFileExtension(
    base::FilePath::StringViewType file_extension);

std::vector<std::string> GetSupportedMimetypes();

}  // namespace playlist::mime_util

#endif  // CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_MIME_UTIL_H_
