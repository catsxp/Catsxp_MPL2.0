/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_NTP_BACKGROUND_NTP_BACKGROUND_PREFS_H_
#define CATSXP_BROWSER_NTP_BACKGROUND_NTP_BACKGROUND_PREFS_H_

#include <string>
#include <variant>
#include <vector>

#include "base/memory/raw_ptr.h"

namespace base {
class DictValue;
}  // namespace base

namespace user_prefs {
class PrefRegistrySyncable;
}  // namespace user_prefs

class PrefService;

// NTPBackgroundPrefs gives easy access to values for NTP background from prefs.
// The data is stored in following format:
//
//  kNTPBackground: {
//     type: ‘catsxp’ | ‘custom_image’ | 'color' | ‘solid_color’
//     random: bool  // indicates that we should pick one every time
//                      from |selected_type| collection
//     selected_value?: string  // url or css value
// }
//
//  Types:
//   'catsxp': mapped to Type::kCatsxp. Default backgrounds provided by us.
//            |selected_value| is empty.
//
//   'custom_image': mapped to |Type::kCustomImage.| custom image uploaded by
//                   user. |selected_value| is name of image file.
//
//   'color' | 'solid_color': mapped to |Type::kColor|. |selected_value| is css
//                            value or either one of 'gradient' or ' solid' in
//                            case |ShouldUseRandomValue()| is true. Value name
//                            is kept as 'solid_color' for backward
//                            compatibility.
//
class NTPBackgroundPrefs final {
 public:
  static constexpr char kDeprecatedPrefName[] =
      "catsxp.new_tab_page.custom_background_enabled";
  static constexpr char kPrefName[] = "catsxp.new_tab_page.background";

  static constexpr char kCustomImageListPrefName[] =
      "catsxp.new_tab_page.custom_background_image_list";

  enum class Type {
    kCatsxp,  // Images that we supply.
    kCustomImage,
    kColor,
  };

  explicit NTPBackgroundPrefs(PrefService* service);
  NTPBackgroundPrefs(const NTPBackgroundPrefs& pref) = delete;
  NTPBackgroundPrefs& operator=(const NTPBackgroundPrefs& pref) = delete;
  ~NTPBackgroundPrefs();

  static void RegisterPref(user_prefs::PrefRegistrySyncable* registry);

  // Try to migrate the old pref for custom background into this new pref.
  void MigrateOldPref();

  // Types
  Type GetType() const;
  void SetType(Type type);
  bool IsCatsxpType() const;
  bool IsCustomImageType() const;
  bool IsColorType() const;

  // Returns true when we should pick one item of selected type every time NTP
  // opens.
  bool ShouldUseRandomValue() const;
  void SetShouldUseRandomValue(bool random);

  void SetSelectedValue(const std::string& value);

  // Return a value to use as NTP background.
  std::string GetSelectedValue() const;

  void AddCustomImageToList(const std::string& file_name);
  void RemoveCustomImageFromList(const std::string& file_name);
  std::vector<std::string> GetCustomImageList() const;

 private:
  const base::DictValue* GetPrefValue() const;

  raw_ptr<PrefService> service_ = nullptr;
};

#endif  // CATSXP_BROWSER_NTP_BACKGROUND_NTP_BACKGROUND_PREFS_H_
