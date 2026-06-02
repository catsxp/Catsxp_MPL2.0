/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_DOMAIN_BLOCK_PAGE_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_DOMAIN_BLOCK_PAGE_H_

#include <memory>
#include <string>

#include "components/security_interstitials/content/security_interstitial_page.h"
#include "url/gurl.h"

namespace base {
class DictValue;
}  // namespace base

namespace content {
class WebContents;
}  // namespace content

namespace security_interstitials {
class SecurityInterstitialControllerClient;
}  // namespace security_interstitials

namespace catsxp_shields {

// DomainBlockPage is the interstitial page which will be shown when the
// browser blocks a top-level, first-party request. A proceed button is
// provided in the page, along with a checkbox to whitelist the domain and
// bypass this interstitial for this domain in the future.
class DomainBlockPage
    : public security_interstitials::SecurityInterstitialPage {
 public:
  // Interstitial type, used in tests.
  static const security_interstitials::SecurityInterstitialPage::TypeID
      kTypeForTesting;

  DomainBlockPage(
      content::WebContents* web_contents,
      const GURL& request_url,
      std::unique_ptr<
          security_interstitials::SecurityInterstitialControllerClient>
          controller);
  ~DomainBlockPage() override;

  DomainBlockPage(const DomainBlockPage&) = delete;
  DomainBlockPage& operator=(const DomainBlockPage&) = delete;

  // SecurityInterstitialPage:: overrides
  void OnInterstitialClosing() override {}
  void CommandReceived(const std::string& command) override;
  security_interstitials::SecurityInterstitialPage::TypeID GetTypeForTesting()
      override;

 protected:
  // SecurityInterstitialPage:: overrides
  void PopulateInterstitialStrings(base::DictValue& load_time_data) override;
  int GetHTMLTemplateId() override;
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_DOMAIN_BLOCK_PAGE_H_
