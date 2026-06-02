/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_CONFIRMATION_QUEUE_DATABASE_TABLE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_CONFIRMATION_QUEUE_DATABASE_TABLE_H_

#include "base/check_op.h"
#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/queue_item/confirmation_queue_item_info.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_table_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads::database::table {

using GetConfirmationQueueCallback = base::OnceCallback<void(
    bool success,
    const ConfirmationQueueItemList& confirmation_queue_items)>;

using GetConfirmationQueueForCreativeInstanceIdCallback =
    base::OnceCallback<void(
        bool success,
        const std::string& creative_instance_id,
        const ConfirmationQueueItemList& confirmation_queue_items)>;

class ConfirmationQueue final : public TableInterface {
 public:
  ConfirmationQueue();

  void Save(const ConfirmationQueueItemList& confirmation_queue_items,
            ResultCallback callback) const;

  void DeleteAll(ResultCallback callback) const;
  void Delete(const std::string& transaction_id, ResultCallback callback) const;

  void Retry(const std::string& transaction_id, ResultCallback callback) const;

  void GetAll(GetConfirmationQueueCallback callback) const;
  void GetNext(GetConfirmationQueueCallback callback) const;

  void SetBatchSize(int batch_size) {
    CHECK_GT(batch_size, 0);

    batch_size_ = batch_size;
  }

  // TableInterface:
  void Create(const mojom::DBTransactionInfoPtr& mojom_db_transaction) override;
  void Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               int to_version) override;

 private:
  int batch_size_;
};

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_CONFIRMATION_QUEUE_DATABASE_TABLE_H_
