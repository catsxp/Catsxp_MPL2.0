/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_PLAYLIST_MEDIA_HANDLER_H_
#define CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_PLAYLIST_MEDIA_HANDLER_H_

#include <variant>
#include <vector>

#include "base/functional/callback_forward.h"
#include "base/values.h"
#include "catsxp/components/playlist/core/common/mojom/playlist.mojom.h"
#include "content/public/browser/render_frame_host_receiver_set.h"
#include "content/public/browser/web_contents_user_data.h"
#include "mojo/public/cpp/bindings/pending_associated_receiver.h"

class GURL;

namespace content {
class RenderFrameHost;
class WebContents;
}  // namespace content

namespace playlist {

// `PlaylistMediaHandler` can receive `OnMediaDetected` messages via a set of
// Channel-associated `mojom::PlaylistMediaResponder` receivers, the other end
// of which reside in renderer processes (in `PlaylistRenderFrameObserver`s)
// that host the sending remote `RenderFrame`s of the `WebContents` that was
// passed to the constructor. `mojom::PlaylistMediaResponder` is exposed to
// `RenderFrame`s in `CatsxpContentBrowserClient`'s
// `RegisterAssociatedInterfaceBindersForRenderFrameHost()`.
// Depending on the callback you pass to
// `PlaylistMediaHandler::CreateForWebContents()`,
// you either get back the first non-empty media list
// (`base::OnceCallback<>` case -
// used by `PlaylistBackgroundWebContentsHelper`),
// or all the non-empty media lists
// (`base::RepeatingCallback<>` case -
// used by `PlaylistTabHelper`), for the lifetime of the `WebContents`.
class PlaylistMediaHandler final
    : public content::WebContentsUserData<PlaylistMediaHandler>,
      public mojom::PlaylistMediaResponder {
  using Signature = void(GURL, std::vector<mojom::PlaylistItemPtr>);

 public:
  using OnceCallback = base::OnceCallback<Signature>;
  using RepeatingCallback = base::RepeatingCallback<Signature>;

  PlaylistMediaHandler(const PlaylistMediaHandler&) = delete;
  PlaylistMediaHandler& operator=(const PlaylistMediaHandler&) = delete;
  ~PlaylistMediaHandler() override;

  static void BindMediaResponderReceiver(
      content::RenderFrameHost* render_frame_host,
      mojo::PendingAssociatedReceiver<mojom::PlaylistMediaResponder> receiver);

 private:
  friend class content::WebContentsUserData<PlaylistMediaHandler>;

  using OnMediaDetectedCallback = std::variant<OnceCallback, RepeatingCallback>;

  PlaylistMediaHandler(content::WebContents* web_contents,
                       OnMediaDetectedCallback on_media_detected_callback);

  // mojom::PlaylistMediaResponder:
  void OnMediaDetected(std::vector<mojom::PlaylistItemPtr> items) override;

  content::RenderFrameHostReceiverSet<mojom::PlaylistMediaResponder>
      media_responder_receivers_;
  OnMediaDetectedCallback on_media_detected_callback_;

  WEB_CONTENTS_USER_DATA_KEY_DECL();
};

}  // namespace playlist

#endif  // CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_PLAYLIST_MEDIA_HANDLER_H_
