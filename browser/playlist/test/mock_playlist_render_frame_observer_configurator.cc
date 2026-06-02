/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/playlist/test/mock_playlist_render_frame_observer_configurator.h"

#include <utility>

#include "mojo/public/cpp/bindings/pending_associated_receiver.h"

namespace playlist {
MockPlaylistRenderFrameObserverConfigurator::
    MockPlaylistRenderFrameObserverConfigurator() = default;

MockPlaylistRenderFrameObserverConfigurator::
    ~MockPlaylistRenderFrameObserverConfigurator() = default;

void MockPlaylistRenderFrameObserverConfigurator::BindReceiver(
    mojo::ScopedInterfaceEndpointHandle handle) {
  ASSERT_FALSE(receiver_);
  receiver_.Bind(
      mojo::PendingAssociatedReceiver<
          mojom::PlaylistRenderFrameObserverConfigurator>(std::move(handle)));
}
}  // namespace playlist
