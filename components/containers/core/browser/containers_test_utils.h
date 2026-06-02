/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_CONTAINERS_TEST_UTILS_H_
#define CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_CONTAINERS_TEST_UTILS_H_

#include <string>
#include <utility>
#include <vector>

#include "base/containers/flat_set.h"
#include "catsxp/components/containers/core/browser/containers_service.h"
#include "catsxp/components/containers/core/mojom/containers.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "third_party/skia/include/core/SkColor.h"

namespace containers {

class MockContainersServiceDelegate : public ContainersService::Delegate {
 public:
  MockContainersServiceDelegate();
  ~MockContainersServiceDelegate() override;

  MOCK_METHOD(void,
              GetReferencedContainerIds,
              (OnReferencedContainerIdsReadyCallback),
              (override));
  MOCK_METHOD(void,
              DeleteContainerStorage,
              (const std::string&, DeleteContainerStorageCallback),
              (override));

  void SetReferencedContainersIds(base::flat_set<std::string> ids) {
    referenced_container_ids_ = std::move(ids);
  }

  void set_delete_result(bool delete_result) { delete_result_ = delete_result; }
  const std::vector<std::string>& delete_requests() const {
    return delete_requests_;
  }

 private:
  base::flat_set<std::string> referenced_container_ids_;
  bool delete_result_ = true;
  std::vector<std::string> delete_requests_;
};

mojom::ContainerPtr MakeContainer(std::string id,
                                  std::string name,
                                  mojom::Icon icon = mojom::Icon::kDefault,
                                  SkColor color = SK_ColorBLUE);

void ExpectContainer(const mojom::ContainerPtr& container,
                     const std::string& id,
                     const std::string& name,
                     mojom::Icon icon = mojom::Icon::kDefault,
                     SkColor color = SK_ColorBLUE);

}  // namespace containers

#endif  // CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_CONTAINERS_TEST_UTILS_H_
