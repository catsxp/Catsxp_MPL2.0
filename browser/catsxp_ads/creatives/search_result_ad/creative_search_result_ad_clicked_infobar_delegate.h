/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_CLICKED_INFOBAR_DELEGATE_H_
#define CATSXP_BROWSER_CATSXP_ADS_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_CLICKED_INFOBAR_DELEGATE_H_

#include <string>

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

namespace catsxp_ads {

class CreativeSearchResultAdClickedInfoBarDelegate
    : public CatsxpConfirmInfoBarDelegate {
 public:
  CreativeSearchResultAdClickedInfoBarDelegate();

  CreativeSearchResultAdClickedInfoBarDelegate(
      const CreativeSearchResultAdClickedInfoBarDelegate&) = delete;
  CreativeSearchResultAdClickedInfoBarDelegate& operator=(
      const CreativeSearchResultAdClickedInfoBarDelegate&) = delete;

  ~CreativeSearchResultAdClickedInfoBarDelegate() override;

  static void Create(content::WebContents* web_contents, PrefService* prefs);

 private:
  // ConfirmInfoBarDelegate:
  infobars::InfoBarDelegate::InfoBarIdentifier GetIdentifier() const override;
  ui::ImageModel GetIcon() const override;
  std::u16string GetMessageText() const override;
  int GetButtons() const override;
  std::u16string GetLinkText() const override;
  GURL GetLinkURL() const override;
  bool LinkClicked(WindowOpenDisposition disposition) override;

  // CatsxpConfirmInfoBarDelegate:
  bool ShouldSupportMultiLine() const override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_CLICKED_INFOBAR_DELEGATE_H_
