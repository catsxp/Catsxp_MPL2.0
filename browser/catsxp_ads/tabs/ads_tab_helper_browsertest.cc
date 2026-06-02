/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/tabs/ads_tab_helper.h"

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include "base/callback_list.h"
#include "base/check.h"
#include "base/files/file_path.h"
#include "base/functional/bind.h"
#include "base/functional/callback.h"
#include "base/notreached.h"
#include "base/path_service.h"
#include "base/run_loop.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_split.h"
#include "base/strings/string_util.h"
#include "base/test/gmock_callback_support.h"
#include "base/test/test_future.h"
#include "catsxp/browser/catsxp_ads/ads_service_factory.h"
#include "catsxp/components/catsxp_ads/core/browser/service/test/ads_service_mock.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "catsxp/components/catsxp_rewards/core/pref_names.h"
#include "catsxp/components/constants/catsxp_paths.h"
#include "build/build_config.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/keep_alive/profile_keep_alive_types.h"
#include "chrome/browser/profiles/keep_alive/scoped_profile_keep_alive.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/sessions/session_restore_test_helper.h"
#include "chrome/browser/sessions/session_restore_test_utils.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_commands.h"
#include "chrome/browser/ui/browser_tabstrip.h"
#include "chrome/common/pref_names.h"
#include "chrome/test/base/chrome_test_utils.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/platform_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "components/keep_alive_registry/keep_alive_types.h"
#include "components/keep_alive_registry/scoped_keep_alive.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/prefs/pref_service.h"
#include "components/sessions/content/session_tab_helper.h"
#include "components/sessions/core/session_id.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/media_player_id.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "content/public/test/content_mock_cert_verifier.h"
#include "net/dns/mock_host_resolver.h"
#include "net/http/http_status_code.h"
#include "net/test/embedded_test_server/embedded_test_server.h"
#include "net/test/embedded_test_server/http_request.h"
#include "net/test/embedded_test_server/http_response.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"
#include "url/gurl.h"

// npm run test -- catsxp_browser_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

constexpr std::string_view kHostName = "catsxp.com";

constexpr char kHandleRequestUrlPath[] = "/handle_request";
constexpr char kHttpStatusCodeQueryKey[] = "http_status_code";

constexpr char kMultiPageApplicationWebpage[] =
    "/catsxp_ads/multi_page_application.html";
constexpr char kMultiPageApplicationWebpageTextContent[] =
    "Welcome to Your Adventure\n\nEmbark on a journey of learning and "
    "discovery. Each step you take brings you closer to mastering new skills "
    "and achieving your goals.\n\nExplore new programming "
    "languages\nContribute to open-source projects\nDevelop innovative "
    "applications\n\"The only limit to our realization of tomorrow is our "
    "doubts of today.\" - Franklin D. Roosevelt\nTask\tStatus\nLearn "
    "Rust\tCompleted\nContribute to a GitHub repository\tIn Progress\nBuild a "
    "mobile app\tPending";

constexpr char kSinglePageApplicationWebpage[] =
    "/catsxp_ads/single_page_application.html";
constexpr char kSinglePageApplicationClickSelector[] =
    "[data-navigation-type='same_document']";

constexpr char kAutoplayVideoWebpage[] = "/catsxp_ads/autoplay_video.html";
constexpr char kVideoWebpage[] = "/catsxp_ads/video.html";
constexpr char kVideoJavascriptDocumentQuerySelector[] = "video";

MATCHER_P(FileName, filename, "") {
  return arg.ExtractFileName() == filename;
}

class MediaWaiter final : public content::WebContentsObserver {
 public:
  explicit MediaWaiter(content::WebContents* const web_contents)
      : content::WebContentsObserver(web_contents) {}

  void WaitForMediaStartedPlaying() {
    ASSERT_TRUE(media_started_playing_.Wait());
  }

  void WaitForMediaDestroyed() { ASSERT_TRUE(media_destroyed_.Wait()); }

  void WaitForMediaSessionCreated() {
    ASSERT_TRUE(media_session_created_.Wait());
  }

  void WaitForMediaMutedStatusChanged() {
    if (muted_status_changed_count_ > 0U) {
      --muted_status_changed_count_;
      return;
    }
    base::test::TestFuture<void> future;
    muted_status_changed_callback_ = future.GetCallback();
    ASSERT_TRUE(future.Wait());
  }

  // content::WebContentsObserver:
  void MediaStartedPlaying(const MediaPlayerInfo& /*video_type*/,
                           const content::MediaPlayerId& id) override {
    id_ = id;
    media_started_playing_.SetValue();
  }

  void MediaDestroyed(const content::MediaPlayerId& id) override {
    EXPECT_EQ(id, id_);
    media_destroyed_.SetValue();
  }

  void MediaSessionCreated(
      content::MediaSession* const /*media_session*/) override {
    media_session_created_.SetValue();
  }

  void MediaMutedStatusChanged(const content::MediaPlayerId& /*id*/,
                               bool /*muted*/) override {
    if (muted_status_changed_callback_) {
      std::move(muted_status_changed_callback_).Run();
    } else {
      ++muted_status_changed_count_;
    }
  }

 private:
  std::optional<content::MediaPlayerId> id_;

  base::test::TestFuture<void> media_started_playing_;
  base::test::TestFuture<void> media_destroyed_;
  base::test::TestFuture<void> media_session_created_;

  size_t muted_status_changed_count_ = 0;
  base::OnceClosure muted_status_changed_callback_;
};

std::unique_ptr<KeyedService> CreateAdsService(
    content::BrowserContext* const /*context*/) {
  return std::make_unique<AdsServiceMock>();
}

void OnWillCreateBrowserContextServices(
    content::BrowserContext* const context) {
  AdsServiceFactory::GetInstance()->SetTestingFactory(
      context, base::BindRepeating(&CreateAdsService));
}

std::unique_ptr<net::test_server::HttpResponse> HandleHttpStatusCodeQueryKey(
    const std::string& value) {
  auto http_response = std::make_unique<net::test_server::BasicHttpResponse>();

  int http_status_code_as_int;
  EXPECT_TRUE(base::StringToInt(value, &http_status_code_as_int));
  std::optional<net::HttpStatusCode> http_status_code =
      net::TryToGetHttpStatusCode(http_status_code_as_int);
  EXPECT_TRUE(http_status_code);
  http_response->set_code(*http_status_code);

  http_response->set_content_type("text/html");
  const std::string http_status_code_page = absl::StrFormat(
      R"(
            <html>
              <head>
                <title>
                  HTTP Status Code
                </title>
              </head>
              <body>
                %d (%s)
              </body>
            </html>)",
      *http_status_code, http_response->reason());
  http_response->set_content(http_status_code_page);

  return http_response;
}

std::unique_ptr<net::test_server::HttpResponse> HandleRequest(
    const net::test_server::HttpRequest& http_request) {
  const GURL url = http_request.GetURL();
  if (url.path() != kHandleRequestUrlPath) {
    // Do not handle the request.
    return nullptr;
  }

  // Handle request.
  base::StringPairs key_value_pairs;
  base::SplitStringIntoKeyValuePairs(url.query(), '=', '&', &key_value_pairs);

  for (const auto& [key, value] : key_value_pairs) {
    if (key == kHttpStatusCodeQueryKey) {
      return HandleHttpStatusCodeQueryKey(value);
    }
  }

  NOTREACHED() << "Query key not found. Unable to handle the request.";
}

base::FilePath GetTestDataDir() {
  const base::ScopedAllowBlockingForTesting scoped_allow_blocking;
  return base::PathService::CheckedGet(catsxp::DIR_TEST_DATA);
}

}  // namespace

// We expect `is_visible=true` if both the browser and tab are active, and
// `is_visible=false` if either the browser or tab is inactive. To avoid flaky
// tests caused by the browser becoming inactive, we match on `::testing::_`.

class CatsxpAdsTabHelperTest : public PlatformBrowserTest {
 public:
  void SetUpOnMainThread() override {
    PlatformBrowserTest::SetUpOnMainThread();

    mock_cert_verifier_.mock_cert_verifier()->set_default_result(net::OK);
    host_resolver()->AddRule("*", "127.0.0.1");
    InitEmbeddedTestServer();
  }

  void SetUpCommandLine(base::CommandLine* command_line) override {
    PlatformBrowserTest::SetUpCommandLine(command_line);

    mock_cert_verifier_.SetUpCommandLine(command_line);
  }

  void SetUpInProcessBrowserTestFixture() override {
    PlatformBrowserTest::SetUpInProcessBrowserTestFixture();

    mock_cert_verifier_.SetUpInProcessBrowserTestFixture();

    callback_list_subscription_ =
        BrowserContextDependencyManager::GetInstance()
            ->RegisterCreateServicesCallbackForTesting(
                base::BindRepeating(&OnWillCreateBrowserContextServices));
  }

  void TearDownInProcessBrowserTestFixture() override {
    mock_cert_verifier_.TearDownInProcessBrowserTestFixture();

    PlatformBrowserTest::TearDownInProcessBrowserTestFixture();
  }

  AdsServiceMock& GetAdsServiceMock() {
    AdsService* ads_service = AdsServiceFactory::GetForProfile(GetProfile());
    CHECK(ads_service);
    return *static_cast<AdsServiceMock*>(ads_service);
  }

  Profile* GetProfile() { return chrome_test_utils::GetProfile(this); }

  PrefService* GetPrefs() { return GetProfile()->GetPrefs(); }

  void InitEmbeddedTestServer() {
    const base::FilePath test_data_dir = GetTestDataDir();

    test_server_.ServeFilesFromDirectory(test_data_dir);
    test_server_.RegisterRequestHandler(base::BindRepeating(&HandleRequest));
    test_server_handle_ = test_server_.StartAndReturnHandle();
    EXPECT_TRUE(test_server_handle_);
  }

  content::WebContents* GetActiveWebContents() {
    return chrome_test_utils::GetActiveWebContents(this);
  }

  int32_t TabId() {
    content::WebContents* const web_contents = GetActiveWebContents();
    EXPECT_TRUE(web_contents);

    return sessions::SessionTabHelper::IdForTab(web_contents).id();
  }

  bool WaitForActiveWebContentsToLoad() {
    content::WebContents* const web_contents = GetActiveWebContents();
    EXPECT_TRUE(web_contents);

    web_contents->GetController().LoadIfNecessary();

    return content::WaitForLoadStop(web_contents);
  }

  void CloseActiveWebContents() {
    content::WebContents* const web_contents = GetActiveWebContents();
    chrome::CloseWebContents(browser(), web_contents, /*add_to_history=*/false);
  }

  void NavigateToRelativeURL(std::string_view relative_url,
                             bool has_user_gesture) {
    content::WebContents* const web_contents = GetActiveWebContents();
    EXPECT_TRUE(web_contents);

    const GURL url = test_server_.GetURL(kHostName, relative_url);

    const content::NavigationController::LoadURLParams params(url);
    if (has_user_gesture) {
      return content::NavigateToURLBlockUntilNavigationsComplete(
          web_contents, url, /*number_of_navigations=*/1,
          /*ignore_uncommitted_navigations=*/true);
    }

    EXPECT_TRUE(NavigateToURLFromRendererWithoutUserGesture(web_contents, url));
  }

  void SimulateHttpStatusCodePage(int http_status_code) {
    const std::string relative_url =
        absl::StrFormat("%s?%s=%d", kHandleRequestUrlPath,
                        kHttpStatusCodeQueryKey, http_status_code);
    NavigateToRelativeURL(relative_url, /*has_user_gesture=*/true);
  }

  ::testing::AssertionResult ExecuteJavaScript(const std::string& javascript,
                                               bool has_user_gesture) {
    content::WebContents* const web_contents = GetActiveWebContents();
    return content::ExecJs(web_contents, javascript,
                           has_user_gesture
                               ? content::EXECUTE_SCRIPT_DEFAULT_OPTIONS
                               : content::EXECUTE_SCRIPT_NO_USER_GESTURE);
  }

  void GoBack() {
    content::WebContents* const web_contents = GetActiveWebContents();
    EXPECT_TRUE(web_contents);

    content::NavigationController& navigation_controller =
        web_contents->GetController();
    EXPECT_TRUE(navigation_controller.CanGoBack());
    navigation_controller.GoBack();
  }

  void GoForward() {
    content::WebContents* const web_contents = GetActiveWebContents();
    EXPECT_TRUE(web_contents);

    content::NavigationController& navigation_controller =
        web_contents->GetController();
    EXPECT_TRUE(navigation_controller.CanGoForward());
    navigation_controller.GoForward();
  }

  void Reload() {
    content::WebContents* const web_contents = GetActiveWebContents();
    EXPECT_TRUE(web_contents);

    web_contents->GetController().Reload(content::ReloadType::NORMAL,
                                         /*check_for_repost=*/false);
  }

  void SimulateClick(const std::string& selector, bool has_user_gesture) {
    const std::string javascript = base::ReplaceStringPlaceholders(
        R"(document.querySelector("$1").click();)", {selector}, nullptr);
    ASSERT_TRUE(ExecuteJavaScript(javascript, has_user_gesture));
  }

  void StartVideoPlayback(const std::string& selector) {
    const std::string javascript = base::ReplaceStringPlaceholders(
        R"(document.querySelector("$1")?.play();)", {selector}, nullptr);

    // Video elements must be executed with a user gesture.
    ASSERT_TRUE(ExecuteJavaScript(javascript, /*has_user_gesture=*/true));
  }

  void PauseVideoPlayback(const std::string& selector) {
    const std::string javascript = base::ReplaceStringPlaceholders(
        R"(document.querySelector("$1")?.pause();)", {selector}, nullptr);
    ASSERT_TRUE(ExecuteJavaScript(javascript, /*has_user_gesture=*/true));
  }

  void MuteVideoAudio(const std::string& selector) {
    const std::string javascript = base::ReplaceStringPlaceholders(
        R"(document.querySelector("$1").muted = true;)", {selector}, nullptr);
    ASSERT_TRUE(ExecuteJavaScript(javascript, /*has_user_gesture=*/true));
  }

  void UnmuteVideoAudio(const std::string& selector) {
    const std::string javascript = base::ReplaceStringPlaceholders(
        R"(document.querySelector("$1").muted = false;)", {selector}, nullptr);
    ASSERT_TRUE(ExecuteJavaScript(javascript, /*has_user_gesture=*/true));
  }

  void RestoreBrowser(Profile* const profile) {
    CHECK(profile);

    ui_test_utils::BrowserCreatedObserver browser_created_observer;
    SessionRestoreTestHelper session_restore_test_helper;
    chrome::OpenWindowWithRestoredTabs(profile);
    if (SessionRestore::IsRestoring(profile)) {
      session_restore_test_helper.Wait();
    }

    SetBrowser(browser_created_observer.Wait());
  }

  std::vector<GURL> RedirectChainExpectation(
      std::string_view relative_url) const {
    const GURL url = test_server_.GetURL(kHostName, relative_url);
    return {url};
  }

 private:
  content::ContentMockCertVerifier mock_cert_verifier_;

  base::CallbackListSubscription callback_list_subscription_;

  net::EmbeddedTestServer test_server_{
      net::test_server::EmbeddedTestServer::TYPE_HTTPS};
  net::test_server::EmbeddedTestServerHandle test_server_handle_;
};

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest, NotifyTabDidChange) {
  EXPECT_CALL(
      GetAdsServiceMock(),
      NotifyTabDidChange(TabId(),
                         RedirectChainExpectation(kMultiPageApplicationWebpage),
                         /*is_new_navigation=*/true, /*is_restoring=*/false,
                         /*is_visible=*/::testing::_))
      .Times(::testing::AtLeast(1));
  NavigateToRelativeURL(kMultiPageApplicationWebpage,
                        /*has_user_gesture=*/true);
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       NotifyTabDidChangeIfTabWasRestored) {
  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidChange)
      .Times(::testing::AnyNumber());

  EXPECT_CALL(
      GetAdsServiceMock(),
      NotifyTabDidChange(TabId(),
                         RedirectChainExpectation(kMultiPageApplicationWebpage),
                         /*is_new_navigation=*/true, /*is_restoring=*/false,
                         /*is_visible=*/::testing::_))
      .Times(::testing::AtLeast(1));
  NavigateToRelativeURL(kMultiPageApplicationWebpage,
                        /*has_user_gesture=*/true);

  // Must occur before the browser is closed.
  Profile* const profile = GetProfile();
  AdsServiceMock& ads_service_mock = GetAdsServiceMock();

  const ScopedKeepAlive scoped_keep_alive(KeepAliveOrigin::SESSION_RESTORE,
                                          KeepAliveRestartOption::DISABLED);
  const ScopedProfileKeepAlive scoped_profile_keep_alive(
      profile, ProfileKeepAliveOrigin::kSessionRestore);
  CloseBrowserSynchronously(browser());

  // We do not know the tab id until the tab is restored, so we match on
  // `::testing::_`.
  EXPECT_CALL(ads_service_mock,
              NotifyTabDidChange(
                  /*tab_id=*/::testing::_,
                  RedirectChainExpectation(kMultiPageApplicationWebpage),
                  /*is_new_navigation=*/false, /*is_restoring=*/true,
                  /*is_visible=*/::testing::_));
  RestoreBrowser(profile);

  EXPECT_TRUE(WaitForActiveWebContentsToLoad());
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest, NotifyTabDidLoad) {
  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidLoad(TabId(), net::HTTP_OK));
  NavigateToRelativeURL(kMultiPageApplicationWebpage,
                        /*has_user_gesture=*/true);
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       NotifyTabDidLoadForHttpServerErrorResponsePage) {
  EXPECT_CALL(GetAdsServiceMock(),
              NotifyTabDidLoad(TabId(), net::HTTP_INTERNAL_SERVER_ERROR));
  SimulateHttpStatusCodePage(net::HTTP_INTERNAL_SERVER_ERROR);
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       NotifyTabDidLoadForHttpClientErrorResponsePage) {
  EXPECT_CALL(GetAdsServiceMock(),
              NotifyTabDidLoad(TabId(), net::HTTP_NOT_FOUND));
  SimulateHttpStatusCodePage(net::HTTP_NOT_FOUND);
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       NotifyTabDidLoadForHttpRedirectionResponsePage) {
  EXPECT_CALL(GetAdsServiceMock(),
              NotifyTabDidLoad(TabId(), net::HTTP_MOVED_PERMANENTLY));
  SimulateHttpStatusCodePage(net::HTTP_MOVED_PERMANENTLY);
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       NotifyTabDidLoadForHttpSuccessfulResponsePage) {
  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidLoad(TabId(), net::HTTP_OK));
  SimulateHttpStatusCodePage(net::HTTP_OK);
}

IN_PROC_BROWSER_TEST_F(
    CatsxpAdsTabHelperTest,
    NotifyTabTextContentDidChangeForRewardsUserOptedInToNotificationAds) {
  GetPrefs()->SetBoolean(catsxp_rewards::prefs::kEnabled, true);
  GetPrefs()->SetBoolean(prefs::kOptedInToNotificationAds, true);

  base::RunLoop run_loop;
  EXPECT_CALL(
      GetAdsServiceMock(),
      NotifyTabTextContentDidChange(
          TabId(), RedirectChainExpectation(kMultiPageApplicationWebpage),
          kMultiPageApplicationWebpageTextContent))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  NavigateToRelativeURL(kMultiPageApplicationWebpage,
                        /*has_user_gesture=*/true);
  run_loop.Run();
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       DoNotNotifyTabTextContentDidChangeForNonRewardsUser) {
  GetPrefs()->SetBoolean(catsxp_rewards::prefs::kEnabled, false);

  EXPECT_CALL(GetAdsServiceMock(), NotifyTabTextContentDidChange).Times(0);
  NavigateToRelativeURL(kMultiPageApplicationWebpage,
                        /*has_user_gesture=*/true);
}

IN_PROC_BROWSER_TEST_F(
    CatsxpAdsTabHelperTest,
    DoNotNotifyTabTextContentDidChangeForNonRewardsUserAndOptedOutOfNotificationAds) {
  GetPrefs()->SetBoolean(catsxp_rewards::prefs::kEnabled, false);
  GetPrefs()->SetBoolean(prefs::kOptedInToNotificationAds, false);

  EXPECT_CALL(GetAdsServiceMock(), NotifyTabTextContentDidChange).Times(0);
  NavigateToRelativeURL(kMultiPageApplicationWebpage,
                        /*has_user_gesture=*/true);
}

IN_PROC_BROWSER_TEST_F(
    CatsxpAdsTabHelperTest,
    DoNotNotifyTabTextContentDidChangeForRewardsUserOptedOutOfNotificationAds) {
  GetPrefs()->SetBoolean(catsxp_rewards::prefs::kEnabled, true);
  GetPrefs()->SetBoolean(prefs::kOptedInToNotificationAds, false);

  EXPECT_CALL(GetAdsServiceMock(), NotifyTabTextContentDidChange).Times(0);
  NavigateToRelativeURL(kMultiPageApplicationWebpage,
                        /*has_user_gesture=*/true);
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       DoNotNotifyTabTextContentDidChangeIfTabWasRestored) {
  GetPrefs()->SetBoolean(catsxp_rewards::prefs::kEnabled, true);
  GetPrefs()->SetBoolean(prefs::kOptedInToNotificationAds, true);

  base::RunLoop run_loop;
  EXPECT_CALL(GetAdsServiceMock(), NotifyTabTextContentDidChange)
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  NavigateToRelativeURL(kMultiPageApplicationWebpage,
                        /*has_user_gesture=*/true);
  run_loop.Run();
  ::testing::Mock::VerifyAndClearExpectations(&GetAdsServiceMock());

  // Must occur before the browser is closed.
  Profile* const profile = GetProfile();
  AdsServiceMock& ads_service_mock = GetAdsServiceMock();

  const ScopedKeepAlive scoped_keep_alive(KeepAliveOrigin::SESSION_RESTORE,
                                          KeepAliveRestartOption::DISABLED);
  const ScopedProfileKeepAlive scoped_profile_keep_alive(
      profile, ProfileKeepAliveOrigin::kSessionRestore);
  CloseBrowserSynchronously(browser());

  // We should not notify about changes to the tab's text content, as the
  // session will be restored and the tab will reload.
  EXPECT_CALL(ads_service_mock, NotifyTabTextContentDidChange).Times(0);
  RestoreBrowser(profile);

  EXPECT_TRUE(WaitForActiveWebContentsToLoad());
}

IN_PROC_BROWSER_TEST_F(
    CatsxpAdsTabHelperTest,
    DoNotNotifyTabTextContentDidChangeForPreviouslyCommittedNavigation) {
  GetPrefs()->SetBoolean(catsxp_rewards::prefs::kEnabled, true);
  GetPrefs()->SetBoolean(prefs::kOptedInToNotificationAds, true);

  base::RunLoop run_loop;
  EXPECT_CALL(GetAdsServiceMock(), NotifyTabTextContentDidChange)
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  NavigateToRelativeURL(kMultiPageApplicationWebpage,
                        /*has_user_gesture=*/true);
  run_loop.Run();
  ::testing::Mock::VerifyAndClearExpectations(&GetAdsServiceMock());

  EXPECT_CALL(GetAdsServiceMock(), NotifyTabTextContentDidChange).Times(0);
  GoBack();
  GoForward();
  Reload();

  EXPECT_TRUE(WaitForActiveWebContentsToLoad());
}

IN_PROC_BROWSER_TEST_F(
    CatsxpAdsTabHelperTest,
    DoNotNotifyTabTextContentDidChangeForHttpClientErrorResponsePage) {
  GetPrefs()->SetBoolean(catsxp_rewards::prefs::kEnabled, true);
  GetPrefs()->SetBoolean(prefs::kOptedInToNotificationAds, true);

  EXPECT_CALL(GetAdsServiceMock(), NotifyTabTextContentDidChange).Times(0);
  SimulateHttpStatusCodePage(net::HTTP_NOT_FOUND);
}

IN_PROC_BROWSER_TEST_F(
    CatsxpAdsTabHelperTest,
    DoNotNotifyTabTextContentDidChangeForHttpServerErrorResponsePage) {
  GetPrefs()->SetBoolean(catsxp_rewards::prefs::kEnabled, true);
  GetPrefs()->SetBoolean(prefs::kOptedInToNotificationAds, true);

  EXPECT_CALL(GetAdsServiceMock(), NotifyTabTextContentDidChange).Times(0);
  SimulateHttpStatusCodePage(net::HTTP_INTERNAL_SERVER_ERROR);
}

IN_PROC_BROWSER_TEST_F(
    CatsxpAdsTabHelperTest,
    DoNotNotifyTabTextContentDidChangeForSameDocumentNavigation) {
  GetPrefs()->SetBoolean(catsxp_rewards::prefs::kEnabled, true);
  GetPrefs()->SetBoolean(prefs::kOptedInToNotificationAds, true);

  base::RunLoop run_loop;
  EXPECT_CALL(GetAdsServiceMock(), NotifyTabTextContentDidChange)
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  NavigateToRelativeURL(kSinglePageApplicationWebpage,
                        /*has_user_gesture=*/true);
  run_loop.Run();
  ::testing::Mock::VerifyAndClearExpectations(&GetAdsServiceMock());

  EXPECT_CALL(GetAdsServiceMock(), NotifyTabTextContentDidChange).Times(0);
  SimulateClick(kSinglePageApplicationClickSelector,
                /*has_user_gesture=*/true);

  EXPECT_TRUE(WaitForActiveWebContentsToLoad());
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       NotifyTabDidStartPlayingMediaForAutoplayVideo) {
  GetPrefs()->SetBoolean(::prefs::kAutoplayAllowed, true);

  content::WebContents* const web_contents = GetActiveWebContents();
  MediaWaiter waiter(web_contents);

  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidStartPlayingMedia);
  NavigateToRelativeURL(kAutoplayVideoWebpage, /*has_user_gesture=*/true);

  waiter.WaitForMediaStartedPlaying();
}

IN_PROC_BROWSER_TEST_F(
    CatsxpAdsTabHelperTest,
    DoNotNotifyTabDidStartPlayingMediaForAutoplayVideoIfDisallowed) {
  GetPrefs()->SetBoolean(::prefs::kAutoplayAllowed, false);

  content::WebContents* const web_contents = GetActiveWebContents();
  MediaWaiter waiter(web_contents);

  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidStartPlayingMedia).Times(0);
  NavigateToRelativeURL(kAutoplayVideoWebpage, /*has_user_gesture=*/true);

  waiter.WaitForMediaSessionCreated();
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       NotifyTabDidStopPlayingMediaForAutoplayVideo) {
  GetPrefs()->SetBoolean(::prefs::kAutoplayAllowed, true);

  content::WebContents* const web_contents = GetActiveWebContents();
  MediaWaiter waiter(web_contents);

  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidStartPlayingMedia);
  NavigateToRelativeURL(kAutoplayVideoWebpage, /*has_user_gesture=*/true);

  waiter.WaitForMediaStartedPlaying();

  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidStopPlayingMedia);
  PauseVideoPlayback(kVideoJavascriptDocumentQuerySelector);
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest, NotifyTabDidStartPlayingMedia) {
  NavigateToRelativeURL(kVideoWebpage, /*has_user_gesture=*/true);

  content::WebContents* const web_contents = GetActiveWebContents();
  MediaWaiter waiter(web_contents);

  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidStartPlayingMedia);
  StartVideoPlayback(kVideoJavascriptDocumentQuerySelector);
  waiter.WaitForMediaStartedPlaying();
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest, NotifyTabDidStopPlayingMedia) {
  NavigateToRelativeURL(kVideoWebpage, /*has_user_gesture=*/true);

  StartVideoPlayback(kVideoJavascriptDocumentQuerySelector);

  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidStopPlayingMedia);
  PauseVideoPlayback(kVideoJavascriptDocumentQuerySelector);
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       DoNotNotifyTabDidStartPlayingMediaForMutedVideo) {
  // Arrange
  NavigateToRelativeURL(kVideoWebpage, /*has_user_gesture=*/true);

  content::WebContents* const web_contents = GetActiveWebContents();
  MediaWaiter waiter(web_contents);

  MuteVideoAudio(kVideoJavascriptDocumentQuerySelector);

  // Act & Assert
  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidStartPlayingMedia).Times(0);
  StartVideoPlayback(kVideoJavascriptDocumentQuerySelector);
  waiter.WaitForMediaStartedPlaying();
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       NotifyTabDidStartPlayingMediaWhenVideoIsUnmuted) {
  // Arrange
  NavigateToRelativeURL(kVideoWebpage, /*has_user_gesture=*/true);

  content::WebContents* const web_contents = GetActiveWebContents();
  MediaWaiter waiter(web_contents);

  MuteVideoAudio(kVideoJavascriptDocumentQuerySelector);
  StartVideoPlayback(kVideoJavascriptDocumentQuerySelector);
  waiter.WaitForMediaStartedPlaying();

  // Act & Assert
  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidStartPlayingMedia);
  UnmuteVideoAudio(kVideoJavascriptDocumentQuerySelector);
  waiter.WaitForMediaMutedStatusChanged();
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       NotifyTabDidStopPlayingMediaWhenVideoIsMuted) {
  // Arrange
  NavigateToRelativeURL(kVideoWebpage, /*has_user_gesture=*/true);

  content::WebContents* const web_contents = GetActiveWebContents();
  MediaWaiter waiter(web_contents);

  StartVideoPlayback(kVideoJavascriptDocumentQuerySelector);
  waiter.WaitForMediaStartedPlaying();

  // Act & Assert
  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidStopPlayingMedia);
  MuteVideoAudio(kVideoJavascriptDocumentQuerySelector);
  waiter.WaitForMediaMutedStatusChanged();
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       DoNotNotifyTabDidStopPlayingMediaForMutedVideo) {
  // Arrange
  NavigateToRelativeURL(kVideoWebpage, /*has_user_gesture=*/true);

  content::WebContents* const web_contents = GetActiveWebContents();
  MediaWaiter waiter(web_contents);

  MuteVideoAudio(kVideoJavascriptDocumentQuerySelector);
  StartVideoPlayback(kVideoJavascriptDocumentQuerySelector);
  waiter.WaitForMediaStartedPlaying();

  // Act & Assert
  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidStopPlayingMedia).Times(0);
  PauseVideoPlayback(kVideoJavascriptDocumentQuerySelector);
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       NotifyTabDidStopPlayingMediaWhenVideoIsRemuted) {
  // Arrange
  NavigateToRelativeURL(kVideoWebpage, /*has_user_gesture=*/true);

  content::WebContents* const web_contents = GetActiveWebContents();
  MediaWaiter waiter(web_contents);

  StartVideoPlayback(kVideoJavascriptDocumentQuerySelector);
  waiter.WaitForMediaStartedPlaying();

  MuteVideoAudio(kVideoJavascriptDocumentQuerySelector);
  waiter.WaitForMediaMutedStatusChanged();

  UnmuteVideoAudio(kVideoJavascriptDocumentQuerySelector);
  waiter.WaitForMediaMutedStatusChanged();

  // Act & Assert
  EXPECT_CALL(GetAdsServiceMock(), NotifyTabDidStopPlayingMedia);
  MuteVideoAudio(kVideoJavascriptDocumentQuerySelector);
  waiter.WaitForMediaMutedStatusChanged();
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest, NotifyDidCloseTab) {
  EXPECT_CALL(GetAdsServiceMock(), NotifyDidCloseTab);
  CloseActiveWebContents();
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest, NotifyUserGestureEventTriggered) {
  EXPECT_CALL(GetAdsServiceMock(), NotifyUserGestureEventTriggered)
      .Times(::testing::AtLeast(1));
  NavigateToRelativeURL(kMultiPageApplicationWebpage,
                        /*has_user_gesture=*/true);
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       DoNotNotifyUserGestureEventTriggered) {
  EXPECT_CALL(GetAdsServiceMock(), NotifyUserGestureEventTriggered).Times(0);
  NavigateToRelativeURL(kMultiPageApplicationWebpage,
                        /*has_user_gesture=*/false);
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       DoNotNotifyUserGestureEventTriggeredIfTabWasRestored) {
  EXPECT_CALL(GetAdsServiceMock(), NotifyUserGestureEventTriggered)
      .Times(::testing::AtLeast(1));
  NavigateToRelativeURL(kMultiPageApplicationWebpage,
                        /*has_user_gesture=*/true);
  ::testing::Mock::VerifyAndClearExpectations(&GetAdsServiceMock());

  // Must occur before the browser is closed.
  Profile* const profile = GetProfile();
  AdsServiceMock& ads_service_mock = GetAdsServiceMock();

  const ScopedKeepAlive scoped_keep_alive(KeepAliveOrigin::SESSION_RESTORE,
                                          KeepAliveRestartOption::DISABLED);
  const ScopedProfileKeepAlive scoped_profile_keep_alive(
      profile, ProfileKeepAliveOrigin::kSessionRestore);
  CloseBrowserSynchronously(browser());

  EXPECT_CALL(ads_service_mock, NotifyUserGestureEventTriggered).Times(0);
  RestoreBrowser(profile);

  EXPECT_TRUE(WaitForActiveWebContentsToLoad());
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       CreativeAdsServiceForRegularBrowser) {
  content::WebContents* const web_contents = GetActiveWebContents();
  ASSERT_TRUE(web_contents);

  AdsTabHelper* const ads_tab_helper =
      AdsTabHelper::FromWebContents(web_contents);
  ASSERT_TRUE(ads_tab_helper);

  EXPECT_TRUE(ads_tab_helper->ads_service());
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       DoNotCreativeAdsServiceForIncognitoBrowser) {
  const Browser* const browser = CreateIncognitoBrowser();

  content::WebContents* const web_contents =
      browser->tab_strip_model()->GetActiveWebContents();
  ASSERT_TRUE(web_contents);

  AdsTabHelper* const ads_tab_helper =
      AdsTabHelper::FromWebContents(web_contents);
  ASSERT_TRUE(ads_tab_helper);

  EXPECT_FALSE(ads_tab_helper->ads_service());
}

IN_PROC_BROWSER_TEST_F(CatsxpAdsTabHelperTest,
                       DoNotCreativeAdsServiceForGuestBrowser) {
  const Browser* const browser = CreateGuestBrowser();

  content::WebContents* const web_contents =
      browser->tab_strip_model()->GetActiveWebContents();
  ASSERT_TRUE(web_contents);

  AdsTabHelper* const ads_tab_helper =
      AdsTabHelper::FromWebContents(web_contents);
  ASSERT_TRUE(ads_tab_helper);

  EXPECT_FALSE(ads_tab_helper->ads_service());
}

}  // namespace catsxp_ads
