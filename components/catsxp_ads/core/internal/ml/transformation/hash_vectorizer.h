/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_HASH_VECTORIZER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_HASH_VECTORIZER_H_

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace catsxp_ads::ml {

class HashVectorizer final {
 public:
  HashVectorizer();
  HashVectorizer(int bucket_count, std::vector<uint32_t> subgrams);

  HashVectorizer(const HashVectorizer&) = delete;
  HashVectorizer& operator=(const HashVectorizer&) = delete;

  ~HashVectorizer();

  std::map<uint32_t, double> GetFrequencies(const std::string& html) const;

  std::vector<uint32_t> GetSubstringSizes() const;

  int GetBucketCount() const;

 private:
  std::vector<uint32_t> substring_sizes_;
  int bucket_count_;
};

}  // namespace catsxp_ads::ml

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_HASH_VECTORIZER_H_
