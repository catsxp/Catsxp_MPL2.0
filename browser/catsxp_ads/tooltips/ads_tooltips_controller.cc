/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/tooltips/ads_tooltips_controller.h"

#include <memory>
#include <utility>

#include "catsxp/browser/catsxp_ads/tooltips/ads_captcha_tooltip.h"
#include "catsxp/browser/ui/catsxp_tooltips/catsxp_tooltip_attributes.h"
#include "catsxp/browser/ui/catsxp_tooltips/catsxp_tooltip_popup_handler.h"
#include "components/grit/catsxp_components_strings.h"
#include "ui/base/l10n/l10n_util.h"

namespace catsxp_ads {

AdsTooltipsController::AdsTooltipsController() = default;

AdsTooltipsController::~AdsTooltipsController() = default;

void AdsTooltipsController::ShowCaptchaTooltip(
    const std::string& payment_id,
    const std::string& captcha_id,
    bool include_cancel_button,
    ShowScheduledCaptchaCallback show_captcha_callback,
    SnoozeScheduledCaptchaCallback snooze_captcha_callback) {
  const std::u16string title = l10n_util::GetStringUTF16(
      IDS_CATSXP_ADS_SCHEDULED_CAPTCHA_NOTIFICATION_TITLE);
  const std::u16string body = l10n_util::GetStringUTF16(
      IDS_CATSXP_ADS_SCHEDULED_CAPTCHA_NOTIFICATION_BODY);
  const std::u16string ok_button_text = l10n_util::GetStringUTF16(
      IDS_CATSXP_ADS_SCHEDULED_CAPTCHA_NOTIFICATION_OK_BUTTON_TEXT);
  std::u16string cancel_button_text = l10n_util::GetStringUTF16(
      IDS_CATSXP_ADS_SCHEDULED_CAPTCHA_NOTIFICATION_CANCEL_BUTTON_TEXT);

  catsxp_tooltips::CatsxpTooltipAttributes tooltip_attributes(
      title, body, ok_button_text,
      include_cancel_button ? cancel_button_text : u"");
  tooltip_attributes.set_cancel_button_enabled(include_cancel_button);
  auto captcha_tooltip = std::make_unique<AdsCaptchaTooltip>(
      std::move(show_captcha_callback), std::move(snooze_captcha_callback),
      tooltip_attributes, payment_id, captcha_id);

  // If there's no delegate, set one so that clicks go back to the appropriate
  // handler
  captcha_tooltip->set_delegate(AsWeakPtr());

  catsxp_tooltips::CatsxpTooltipPopupHandler::Show(std::move(captcha_tooltip));
}

void AdsTooltipsController::CloseCaptchaTooltip() {
  catsxp_tooltips::CatsxpTooltipPopupHandler::Close(kScheduledCaptchaTooltipId);
}

base::WeakPtr<catsxp_tooltips::CatsxpTooltipDelegate>
AdsTooltipsController::AsWeakPtr() {
  return weak_ptr_factory_.GetWeakPtr();
}

void AdsTooltipsController::OnTooltipWidgetDestroyed(
    const std::string& /*tooltip_id*/) {
  catsxp_tooltips::CatsxpTooltipPopupHandler::Destroy(kScheduledCaptchaTooltipId);
}

}  // namespace catsxp_ads
