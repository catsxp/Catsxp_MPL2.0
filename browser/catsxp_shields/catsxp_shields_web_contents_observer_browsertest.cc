/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_shields/catsxp_shields_web_contents_observer.h"

#include <memory>

#include "base/memory/raw_ptr.h"
#include "base/path_service.h"
#include "base/values.h"
#include "catsxp/browser/catsxp_browser_process.h"
#include "catsxp/browser/catsxp_shields/ad_block_browser_test_helper.h"
#include "catsxp/browser/catsxp_shields/catsxp_shields_tab_helper.h"
#include "catsxp/components/catsxp_shields/content/browser/ad_block_custom_filters_provider.h"
#include "catsxp/components/catsxp_shields/content/browser/ad_block_service.h"
#include "catsxp/components/catsxp_shields/core/common/catsxp_shield_constants.h"
#include "catsxp/components/constants/catsxp_paths.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/policy/core/browser/browser_policy_connector.h"
#include "components/policy/core/common/mock_configuration_policy_provider.h"
#include "components/policy/core/common/policy_map.h"
#include "components/policy/policy_constants.h"
#include "content/public/browser/web_contents.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "net/dns/mock_host_resolver.h"
#include "url/gurl.h"

namespace catsxp_shields {

namespace {

class TestCatsxpShieldsWebContentsObserver
    : public CatsxpShieldsWebContentsObserver {
 public:
  explicit TestCatsxpShieldsWebContentsObserver(
      content::WebContents* web_contents)
      : CatsxpShieldsWebContentsObserver(web_contents) {}

  // catsxp_shields::mojom::CatsxpShieldsHost.
  void OnJavaScriptBlocked(const std::u16string& details) override {
    CatsxpShieldsWebContentsObserver::OnJavaScriptBlocked(details);
    block_javascript_count_++;
  }

  void Reset() { block_javascript_count_ = 0; }

  int block_javascript_count() { return block_javascript_count_; }

 private:
  int block_javascript_count_ = 0;
};

}  // namespace

class CatsxpShieldsWebContentsObserverBrowserTest : public InProcessBrowserTest {
 public:
  CatsxpShieldsWebContentsObserverBrowserTest() = default;

  void SetUpInProcessBrowserTestFixture() override {
    helper_ = std::make_unique<catsxp_shields::AdBlockBrowserTestHelper>();
  }

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    host_resolver()->AddRule("*", "127.0.0.1");

    base::FilePath test_data_dir;
    base::PathService::Get(catsxp::DIR_TEST_DATA, &test_data_dir);
    embedded_test_server()->ServeFilesFromDirectory(test_data_dir);

    ASSERT_TRUE(embedded_test_server()->Start());
    content_settings_ =
        HostContentSettingsMapFactory::GetForProfile(browser()->profile());

    // We can't simply create a new CatsxpShieldsWebContentsObserver for the same
    // WebContents, as that class will instatiate a RenderFrameHostReceiverSet
    // and we won't be able to intercept the mojo messages received for the
    // catsxp_shields::mojom::CatsxpShieldsHost interface for testing purposes.
    // Instead we call SetReceiverImplForTesting() to make sure that the mojo
    // receiver will be bound to our TestCatsxpShieldsWebContentsObserver class,
    // allowing us to intercept any message we are interested in.
    catsxp_shields_web_contents_observer_ =
        new TestCatsxpShieldsWebContentsObserver(GetWebContents());
    CatsxpShieldsWebContentsObserver::SetReceiverImplForTesting(
        catsxp_shields_web_contents_observer_);
  }

  std::vector<GURL> GetBlockedJsList() {
    return catsxp_shields::CatsxpShieldsTabHelper::FromWebContents(
               GetWebContents())
        ->GetBlockedJsList();
  }

  std::vector<GURL> GetAllowedJsList() {
    return catsxp_shields::CatsxpShieldsTabHelper::FromWebContents(
               GetWebContents())
        ->GetAllowedJsList();
  }

  void ClearAllResourcesList() {
    return catsxp_shields::CatsxpShieldsTabHelper::FromWebContents(
               GetWebContents())
        ->ClearAllResourcesList();
  }

  void TearDownOnMainThread() override {
    helper_.reset();
    CatsxpShieldsWebContentsObserver::SetReceiverImplForTesting(nullptr);
  }

  content::WebContents* GetWebContents() {
    return browser()->tab_strip_model()->GetActiveWebContents();
  }

  HostContentSettingsMap* content_settings() { return content_settings_; }

  TestCatsxpShieldsWebContentsObserver* catsxp_shields_web_contents_observer() {
    return catsxp_shields_web_contents_observer_;
  }

 private:
  std::unique_ptr<catsxp_shields::AdBlockBrowserTestHelper> helper_;
  raw_ptr<HostContentSettingsMap> content_settings_ = nullptr;
  raw_ptr<TestCatsxpShieldsWebContentsObserver>
      catsxp_shields_web_contents_observer_ = nullptr;
};

class CatsxpShieldsWebContentsObserverManagedPolicyBrowserTest
    : public CatsxpShieldsWebContentsObserverBrowserTest {
 public:
  CatsxpShieldsWebContentsObserverManagedPolicyBrowserTest() = default;

  void SetUpOnMainThread() override {
    CatsxpShieldsWebContentsObserverBrowserTest::SetUpOnMainThread();
  }

  void SetUpInProcessBrowserTestFixture() override {
    EXPECT_CALL(provider_, IsInitializationComplete(testing::_))
        .WillRepeatedly(testing::Return(true));
    policy::BrowserPolicyConnector::SetPolicyProviderForTesting(&provider_);
    policy::PolicyMap policies;

    // Set JavaScript blocked for URLs policy
    policies.Set(policy::key::kJavaScriptAllowedForUrls,
                 policy::POLICY_LEVEL_MANDATORY, policy::POLICY_SCOPE_USER,
                 policy::POLICY_SOURCE_PLATFORM, base::Value(), nullptr);
    auto blocked_list = base::ListValue().Append("http://a.com");
    policies.Set(policy::key::kJavaScriptBlockedForUrls,
                 policy::POLICY_LEVEL_MANDATORY, policy::POLICY_SCOPE_USER,
                 policy::POLICY_SOURCE_PLATFORM,
                 base::Value(std::move(blocked_list)), nullptr);
    provider_.UpdateChromePolicy(policies);
  }

 private:
  policy::MockConfigurationPolicyProvider provider_;
};

IN_PROC_BROWSER_TEST_F(CatsxpShieldsWebContentsObserverManagedPolicyBrowserTest,
                       JavaScriptBlockedEvents) {
  auto a_com_url = GURL("http://a.com");
  auto b_com_url = GURL("http://b.com");

  // Verify that the policy is applied correctly
  ContentSetting a_com_javascript_setting =
      content_settings()->GetContentSetting(a_com_url, a_com_url,
                                            ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, a_com_javascript_setting);
  ContentSetting b_com_javascript_setting =
      content_settings()->GetContentSetting(b_com_url, b_com_url,
                                            ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, b_com_javascript_setting);

  // Navigate to the to the a.com URL which has JavaScript blocked by policy
  EXPECT_TRUE(ui_test_utils::NavigateToURL(
      browser(), embedded_test_server()->GetURL("a.com", "/load_js.html")));
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_EQ(catsxp_shields_web_contents_observer()->block_javascript_count(), 5);
  EXPECT_EQ(GetBlockedJsList().size(), 3u);
}

IN_PROC_BROWSER_TEST_F(CatsxpShieldsWebContentsObserverBrowserTest,
                       JavaScriptBlockedEvents) {
  const GURL& url = GURL("a.com");

  // Start with JavaScript blocking initially disabled.
  ContentSetting block_javascript_setting =
      content_settings()->GetContentSetting(url, url,
                                            ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, block_javascript_setting);

  // Load a simple HTML that attempts to load some JavaScript without blocking.
  EXPECT_TRUE(ui_test_utils::NavigateToURL(
      browser(), embedded_test_server()->GetURL("a.com", "/load_js.html")));
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_EQ(catsxp_shields_web_contents_observer()->block_javascript_count(), 0);
  EXPECT_EQ(GetBlockedJsList().size(), 0u);
  // Enable JavaScript blocking globally now.
  content_settings()->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, CONTENT_SETTING_BLOCK);
  block_javascript_setting = content_settings()->GetContentSetting(
      url, url, ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, block_javascript_setting);

  // Reload the test page now that JavaScript has been blocked.
  catsxp_shields_web_contents_observer()->Reset();
  GetWebContents()->GetController().Reload(content::ReloadType::NORMAL, true);
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_GT(catsxp_shields_web_contents_observer()->block_javascript_count(), 0);
  EXPECT_EQ(GetBlockedJsList().size(), 3u);

  // Disable JavaScript blocking again now.
  content_settings()->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, CONTENT_SETTING_ALLOW);
  block_javascript_setting = content_settings()->GetContentSetting(
      url, url, ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, block_javascript_setting);

  // Reload the test page now that JavaScript has been allowed again.
  // Do it twice, because first reload will still trigger blocked events as
  // renderer caches AllowScript results in
  // ContentSettingsAgentImpl::cached_script_permissions_.
  GetWebContents()->GetController().Reload(content::ReloadType::NORMAL, true);
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));

  catsxp_shields_web_contents_observer()->Reset();
  GetWebContents()->GetController().Reload(content::ReloadType::NORMAL, true);
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_EQ(catsxp_shields_web_contents_observer()->block_javascript_count(), 0);
  EXPECT_EQ(GetBlockedJsList().size(), 0u);
}

IN_PROC_BROWSER_TEST_F(CatsxpShieldsWebContentsObserverBrowserTest,
                       EmbeddedJavaScriptTriggersBlockedEvent) {
  // Enable JavaScript blocking globally.
  content_settings()->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, CONTENT_SETTING_BLOCK);

  // Load a simple HTML that attempts to run some JavaScript.
  EXPECT_TRUE(ui_test_utils::NavigateToURL(
      browser(), embedded_test_server()->GetURL("a.com", "/embedded_js.html")));
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_GT(catsxp_shields_web_contents_observer()->block_javascript_count(), 0);
  EXPECT_EQ(GetBlockedJsList().size(), 1u);
}

IN_PROC_BROWSER_TEST_F(CatsxpShieldsWebContentsObserverBrowserTest,
                       JavaScriptAllowedEvents) {
  const GURL& url = GURL("a.com");

  // Start with JavaScript blocking initially disabled.
  ContentSetting block_javascript_setting =
      content_settings()->GetContentSetting(url, url,
                                            ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, block_javascript_setting);

  // Load a simple HTML that attempts to load some JavaScript without blocking.
  EXPECT_TRUE(ui_test_utils::NavigateToURL(
      browser(), embedded_test_server()->GetURL("a.com", "/load_js.html")));
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_EQ(catsxp_shields_web_contents_observer()->block_javascript_count(), 0);

  // Enable JavaScript blocking globally now.
  content_settings()->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, CONTENT_SETTING_BLOCK);
  block_javascript_setting = content_settings()->GetContentSetting(
      url, url, ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, block_javascript_setting);

  // Reload the test page now that JavaScript has been blocked.
  catsxp_shields_web_contents_observer()->Reset();
  GetWebContents()->GetController().Reload(content::ReloadType::NORMAL, true);
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_GT(catsxp_shields_web_contents_observer()->block_javascript_count(), 0);
  auto blocked_list = GetBlockedJsList();
  EXPECT_EQ(blocked_list.size(), 3u);

  // Allow One Script
  catsxp_shields_web_contents_observer()->AllowScriptsOnce(
      std::vector<std::string>({blocked_list.back().spec()}));
  ClearAllResourcesList();
  GetWebContents()->GetController().Reload(content::ReloadType::NORMAL, true);
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_EQ(GetBlockedJsList().size(), 2u);
  EXPECT_EQ(GetAllowedJsList().size(), 1u);

  blocked_list.pop_back();
  EXPECT_EQ(blocked_list.size(), 2u);

  // Allow Second Script
  catsxp_shields_web_contents_observer()->AllowScriptsOnce(
      std::vector<std::string>({blocked_list.back().spec()}));
  ClearAllResourcesList();
  GetWebContents()->GetController().Reload(content::ReloadType::NORMAL, true);
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_EQ(GetBlockedJsList().size(), 1u);
  EXPECT_EQ(GetAllowedJsList().size(), 2u);

  // Block one of allowed scripts.
  catsxp_shields_web_contents_observer()->BlockAllowedScripts(
      {blocked_list.back().spec()});
  ClearAllResourcesList();
  GetWebContents()->GetController().Reload(content::ReloadType::NORMAL, true);
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_EQ(GetBlockedJsList().size(), 2u);
  EXPECT_EQ(GetAllowedJsList().size(), 1u);

  catsxp_shields_web_contents_observer()->BlockAllowedScripts(
      {url::Origin::Create(blocked_list.back()).Serialize()});
  ClearAllResourcesList();
  GetWebContents()->GetController().Reload(content::ReloadType::NORMAL, true);
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_EQ(GetBlockedJsList().size(), 3u);
  EXPECT_EQ(GetAllowedJsList().size(), 0u);

  // Disable JavaScript blocking again now.
  content_settings()->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, CONTENT_SETTING_ALLOW);
  block_javascript_setting = content_settings()->GetContentSetting(
      url, url, ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, block_javascript_setting);

  // Reload the test page now that JavaScript has been allowed again.
  // Do it twice, because first reload will still trigger blocked events as
  // renderer caches AllowScript results in
  // ContentSettingsAgentImpl::cached_script_permissions_.
  GetWebContents()->GetController().Reload(content::ReloadType::NORMAL, true);
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));

  catsxp_shields_web_contents_observer()->Reset();
  GetWebContents()->GetController().Reload(content::ReloadType::NORMAL, true);
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_EQ(catsxp_shields_web_contents_observer()->block_javascript_count(), 0);
}

IN_PROC_BROWSER_TEST_F(CatsxpShieldsWebContentsObserverBrowserTest,
                       JavaScriptAllowedDataUrls) {
  const GURL& url = GURL("a.com");

  // Start with JavaScript blocking initially disabled.
  ContentSetting block_javascript_setting =
      content_settings()->GetContentSetting(url, url,
                                            ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, block_javascript_setting);

  // Enable JavaScript blocking globally now.
  content_settings()->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, CONTENT_SETTING_BLOCK);
  block_javascript_setting = content_settings()->GetContentSetting(
      url, url, ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, block_javascript_setting);

  // Load a simple HTML that attempts to load some JavaScript with data urls.
  auto page_url =
      embedded_test_server()->GetURL("a.com", "/load_js_dataurls.html");
  EXPECT_TRUE(ui_test_utils::NavigateToURL(browser(), page_url));
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_EQ(catsxp_shields_web_contents_observer()->block_javascript_count(), 4);
  catsxp_shields_web_contents_observer()->Reset();
  // Allow subframe script and check we still block his data urls.
  std::string subframe_script =
      url::Origin::Create(page_url).Serialize() + "/load_js_dataurls.js";
  catsxp_shields_web_contents_observer()->AllowScriptsOnce(
      std::vector<std::string>({subframe_script}));
  ClearAllResourcesList();
  GetWebContents()->GetController().Reload(content::ReloadType::NORMAL, true);
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));
  EXPECT_EQ(GetBlockedJsList().size(), 1u);
  EXPECT_EQ(GetAllowedJsList().size(), 1u);
  EXPECT_EQ(catsxp_shields_web_contents_observer()->block_javascript_count(), 3);
  catsxp_shields_web_contents_observer()->Reset();

  // Allow all scripts for domain.
  catsxp_shields_web_contents_observer()->AllowScriptsOnce(
      std::vector<std::string>({url::Origin::Create(page_url).Serialize()}));
  ClearAllResourcesList();
  GetWebContents()->GetController().Reload(content::ReloadType::NORMAL, true);
  EXPECT_TRUE(WaitForLoadStop(GetWebContents()));

  EXPECT_EQ(GetAllowedJsList().size(), 2u);
  EXPECT_EQ(catsxp_shields_web_contents_observer()->block_javascript_count(), 0);
}

IN_PROC_BROWSER_TEST_F(CatsxpShieldsWebContentsObserverBrowserTest,
                       DelayedBlocks) {
  catsxp_shields::AdBlockService* ad_block_service =
      g_catsxp_browser_process->ad_block_service();
  ad_block_service->custom_filters_provider()->UpdateCustomFilters("||b.com^");

  class EmptyAdsBlocked : public CatsxpShieldsTabHelper::Observer {
   public:
    EmptyAdsBlocked(content::WebContents* tab, bool wait_for_empty)
        : tab_(tab), wait_for_empty_(wait_for_empty) {
      auto* tab_helper = CatsxpShieldsTabHelper::FromWebContents(tab_);
      observation_.Observe(tab_helper);
    }

    ~EmptyAdsBlocked() override = default;

    void OnResourcesChanged() override {
      auto* tab_helper = CatsxpShieldsTabHelper::FromWebContents(tab_);
      if (tab_helper->GetBlockedAdsList().empty() == wait_for_empty_) {
        run_loop_.Quit();
      }
    }

    void Wait() { run_loop_.Run(); }

   private:
    const raw_ptr<content::WebContents> tab_ = nullptr;
    const bool wait_for_empty_ = true;
    base::ScopedObservation<CatsxpShieldsTabHelper,
                            CatsxpShieldsTabHelper::Observer>
        observation_{this};
    base::RunLoop run_loop_;
  };

  auto* a_page = ui_test_utils::NavigateToURL(
      browser(), embedded_test_server()->GetURL("a.com", "/simple.html"));

  {
    // Open a.com and start spaming requests to the blocked host.
    constexpr char kScript[] = R"js(
      setInterval( () => {
        fetch($1)
      }, 100)
    )js";

    EmptyAdsBlocked not_empty_waiter(GetWebContents(), false);
    ASSERT_TRUE(content::ExecJs(
        a_page, content::JsReplace(kScript, embedded_test_server()->GetURL(
                                                "b.com", "/simple.html"))));

    // Wait for at least one blocking report.
    not_empty_waiter.Wait();
  }

  {
    EmptyAdsBlocked empty_waiter(GetWebContents(), true);
    ASSERT_TRUE(ui_test_utils::NavigateToURL(
        browser(), embedded_test_server()->GetURL("c.com", "/simple.html")));
    // Wait the reports are cleared on finish navigation.
    empty_waiter.Wait();
  }

  {
    // The straight variant: waiting a delayed report for 1 second.
    base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
    base::SingleThreadTaskRunner::GetCurrentDefault()->PostDelayedTask(
        FROM_HERE, run_loop.QuitClosure(), base::Seconds(1));
    run_loop.Run();

    auto* tab_helper = CatsxpShieldsTabHelper::FromWebContents(GetWebContents());
    EXPECT_EQ(0u, tab_helper->GetBlockedAdsList().size());
  }

  {
    // The synthetic variant: if straight is false positive.
    catsxp_shields::CatsxpShieldsWebContentsObserver::DispatchBlockedEvent(
        GURL("https://test-request.com"), a_page->GetGlobalFrameToken(), kAds);
    auto* tab_helper = CatsxpShieldsTabHelper::FromWebContents(GetWebContents());
    EXPECT_EQ(0u, tab_helper->GetBlockedAdsList().size());
  }
}

}  // namespace catsxp_shields
