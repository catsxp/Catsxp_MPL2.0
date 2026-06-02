/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_NTP_BACKGROUND_NEW_TAB_TAKEOVER_INFOBAR_DELEGATE_H_
#define CATSXP_BROWSER_NTP_BACKGROUND_NEW_TAB_TAKEOVER_INFOBAR_DELEGATE_H_

#include <string>

#include "base/memory/raw_ptr.h"
#include "catsxp/components/infobars/core/catsxp_confirm_infobar_delegate.h"
#include "components/infobars/core/infobar_delegate.h"

class PrefService;
class GURL;
enum class WindowOpenDisposition;

namespace content {
class WebContents;
}  // namespace content

namespace ui {
class ImageModel;
}  // namespace ui

namespace ntp_background_images {

class NewTabTakeoverInfoBarDelegate : public CatsxpConfirmInfoBarDelegate {
 public:
  explicit NewTabTakeoverInfoBarDelegate(PrefService* prefs);

  NewTabTakeoverInfoBarDelegate(const NewTabTakeoverInfoBarDelegate&) = delete;
  NewTabTakeoverInfoBarDelegate& operator=(
      const NewTabTakeoverInfoBarDelegate&) = delete;

  ~NewTabTakeoverInfoBarDelegate() override;

  static void MaybeDisplayAndIncrementCounter(
      content::WebContents* web_contents,
      PrefService* prefs);

 private:
  // ConfirmInfoBarDelegate:
  infobars::InfoBarDelegate::InfoBarIdentifier GetIdentifier() const override;
  ui::ImageModel GetIcon() const override;
  std::u16string GetMessageText() const override;
  int GetButtons() const override;
  std::u16string GetLinkText() const override;
  GURL GetLinkURL() const override;
  bool LinkClicked(WindowOpenDisposition disposition) override;
  void InfoBarDismissed() override;

  // CatsxpConfirmInfoBarDelegate:
  bool ShouldSupportMultiLine() const override;

 private:
  const raw_ptr<PrefService> prefs_;
};

}  // namespace ntp_background_images

#endif  // CATSXP_BROWSER_NTP_BACKGROUND_NEW_TAB_TAKEOVER_INFOBAR_DELEGATE_H_
