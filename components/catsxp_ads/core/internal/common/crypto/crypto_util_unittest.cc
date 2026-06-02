/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/crypto/crypto_util.h"

#include <iterator>

#include "base/base64.h"
#include "catsxp/components/catsxp_ads/core/internal/common/crypto/key_pair_info.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "tweetnacl.h"  // NOLINT

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::crypto {

namespace {

constexpr char kMessage[] = "The quick brown fox jumps over the lazy dog";
constexpr char kPublicKeyBase64[] =
    "5LmgyD6OG0qcVeRgTzk3IWbzSWjemE4KpjTRtRW4eRk=";
constexpr char kSecretKeyBase64[] =
    R"(oyd1rHNB5xHU6TzPSO/MUUfUJNHiol1ExFHMMKV/7dvkuaDIPo4bSpxV5GBPOTchZvNJaN6YTgqmNNG1Fbh5GQ==)";

}  // namespace

TEST(CatsxpAdsCryptoUtilTest, Sha256) {
  // Act
  const std::vector<uint8_t> sha256 = Sha256(kMessage);

  // Assert
  EXPECT_EQ("16j7swfXgJRpypq8sAguT41WUeRtPNt2LQLQvzfJ5ZI=",
            base::Base64Encode(sha256));
}

TEST(CatsxpAdsCryptoUtilTest, Sha256WithEmptyString) {
  // Act
  const std::vector<uint8_t> sha256 = Sha256(/*value=*/"");

  // Assert
  EXPECT_EQ("47DEQpj8HBSa+/TImW+5JCeuQeRkm5NMpJWZG3hSuFU=",
            base::Base64Encode(sha256));
}

TEST(CatsxpAdsCryptoUtilTest, GenerateSignKeyPairFromSeed) {
  // Arrange
  std::optional<std::vector<uint8_t>> seed =
      base::Base64Decode("x5uBvgI5MTTVY6sjGv65e9EHr8v7i+UxkFB9qVc5fP0=");
  ASSERT_TRUE(seed);

  // Act
  std::optional<KeyPairInfo> key_pair = GenerateSignKeyPairFromSeed(*seed);

  // Assert
  ASSERT_TRUE(key_pair);
  ASSERT_THAT(key_pair->public_key,
              ::testing::SizeIs(crypto_sign_ed25519_PUBLICKEYBYTES));
  ASSERT_THAT(key_pair->secret_key,
              ::testing::SizeIs(crypto_sign_ed25519_SECRETKEYBYTES));
  EXPECT_TRUE(key_pair->IsValid());
}

TEST(CatsxpAdsCryptoUtilTest, DoesNotGenerateSignKeyPairFromSeedWithEmptySeed) {
  // Act & Assert
  EXPECT_FALSE(GenerateSignKeyPairFromSeed(/*seed=*/{}));
}

TEST(CatsxpAdsCryptoUtilTest, GenerateBoxKeyPair) {
  // Act
  const KeyPairInfo key_pair = GenerateBoxKeyPair();

  // Assert
  ASSERT_THAT(key_pair.public_key,
              ::testing::SizeIs(crypto_box_PUBLICKEYBYTES));
  ASSERT_THAT(key_pair.secret_key,
              ::testing::SizeIs(crypto_box_SECRETKEYBYTES));
  EXPECT_TRUE(key_pair.IsValid());
}

TEST(CatsxpAdsCryptoUtilTest, GenerateRandomNonce) {
  // Act & Assert
  EXPECT_THAT(GenerateRandomNonce(), ::testing::SizeIs(crypto_box_NONCEBYTES));
}

TEST(CatsxpAdsCryptoUtilTest, Sign) {
  // Act & Assert
  EXPECT_TRUE(Sign(kMessage, kSecretKeyBase64));
}

TEST(CatsxpAdsCryptoUtilTest, DoesNotSignWithInvalidSecretKey) {
  // Act & Assert
  EXPECT_FALSE(Sign(kMessage, /*secret_key_base64=*/"!"));
}

TEST(CatsxpAdsCryptoUtilTest, DoesNotSignWithMalformedSecretKey) {
  // Act & Assert
  EXPECT_FALSE(Sign(kMessage, /*secret_key_base64=*/"AA=="));
}

TEST(CatsxpAdsCryptoUtilTest, Verify) {
  // Arrange
  std::optional<std::string> signature = Sign(kMessage, kSecretKeyBase64);
  ASSERT_TRUE(signature);

  // Act & Assert
  EXPECT_TRUE(Verify(kMessage, kPublicKeyBase64, *signature));
}

TEST(CatsxpAdsCryptoUtilTest, DoesNotVerifyWithInvalidPublicKey) {
  // Act & Assert
  EXPECT_FALSE(
      Verify(kMessage, /*public_key_base64=*/"!", /*signature_base64=*/"AA=="));
}

TEST(CatsxpAdsCryptoUtilTest, DoesNotVerifyWithMalformedPublicKey) {
  // Act & Assert
  EXPECT_FALSE(Verify(kMessage, /*public_key_base64=*/"AA==",
                      /*signature_base64=*/"AA=="));
}

TEST(CatsxpAdsCryptoUtilTest, DoesNotVerifyWithInvalidSignature) {
  // Act & Assert
  EXPECT_FALSE(Verify(kMessage, kPublicKeyBase64, /*signature_base64=*/"!"));
}

TEST(CatsxpAdsCryptoUtilTest, DoesNotVerifyWithMalformedSignature) {
  // Act & Assert
  EXPECT_FALSE(Verify(kMessage, kPublicKeyBase64, /*signature_base64=*/"AA=="));
}

TEST(CatsxpAdsCryptoUtilTest, DoesNotVerifyWithTamperedMessage) {
  // Arrange
  std::optional<std::string> signature = Sign(kMessage, kSecretKeyBase64);
  ASSERT_TRUE(signature);

  // Act & Assert
  EXPECT_FALSE(Verify(/*message=*/"foo", kPublicKeyBase64, *signature));
}

TEST(CatsxpAdsCryptoUtilTest, EncryptAndDecrypt) {
  // Arrange
  const KeyPairInfo key_pair = GenerateBoxKeyPair();
  const KeyPairInfo ephemeral_key_pair = GenerateBoxKeyPair();
  const std::vector<uint8_t> nonce = GenerateRandomNonce();
  const std::vector<uint8_t> plaintext(std::cbegin(kMessage),
                                       std::cend(kMessage));

  // Act
  const std::vector<uint8_t> ciphertext = Encrypt(
      plaintext, nonce, key_pair.public_key, ephemeral_key_pair.secret_key);

  // Assert
  EXPECT_EQ(plaintext,
            MaybeDecrypt(ciphertext, nonce, ephemeral_key_pair.public_key,
                         key_pair.secret_key));
}

TEST(CatsxpAdsCryptoUtilTest, SecureZeroBuffer) {
  // Arrange
  std::vector<uint8_t> buffer = {1, 2, 3, 4};

  // Act
  SecureZero(buffer);

  // Assert
  EXPECT_THAT(buffer, ::testing::Each(uint8_t{0}));
}

TEST(CatsxpAdsCryptoUtilTest, SecureZeroEmptyBuffer) {
  // Arrange
  std::vector<uint8_t> buffer;

  // Act & Assert
  EXPECT_NO_FATAL_FAILURE(SecureZero(buffer));
}

TEST(CatsxpAdsCryptoUtilTest, SecureZeroString) {
  // Arrange
  std::string string = "sensitive";

  // Act
  SecureZero(string);

  // Assert
  EXPECT_THAT(string, ::testing::Each('\0'));
}

TEST(CatsxpAdsCryptoUtilTest, SecureZeroEmptyString) {
  // Arrange
  std::string string;

  // Act & Assert
  EXPECT_NO_FATAL_FAILURE(SecureZero(string));
}

TEST(CatsxpAdsCryptoUtilTest, DoesNotDecryptWithWrongKey) {
  // Arrange
  const KeyPairInfo key_pair = GenerateBoxKeyPair();
  const KeyPairInfo ephemeral_key_pair = GenerateBoxKeyPair();
  const KeyPairInfo wrong_key_pair = GenerateBoxKeyPair();
  const std::vector<uint8_t> nonce = GenerateRandomNonce();
  const std::vector<uint8_t> plaintext(std::cbegin(kMessage),
                                       std::cend(kMessage));
  const std::vector<uint8_t> ciphertext = Encrypt(
      plaintext, nonce, key_pair.public_key, ephemeral_key_pair.secret_key);

  // Act & Assert
  EXPECT_FALSE(MaybeDecrypt(ciphertext, nonce, ephemeral_key_pair.public_key,
                            wrong_key_pair.secret_key));
}

}  // namespace catsxp_ads::crypto
