#include <openssl/sha.h>
#include <string>

#include "SerialHasher.h"

const size_t Sha256Hasher::kDigestSize = SHA256_DIGEST_LENGTH;

Sha256Hasher::Sha256Hasher() : initialized_(false) {}

Sha256Hasher::~Sha256Hasher() {}

void Sha256Hasher::Reset() {
  SHA256_Init(&ctx_);
  initialized_ = true;
}

void Sha256Hasher::Update(const std::string &data) {
  if (!initialized_) {
    Reset();
  }
  SHA256_Update(&ctx_, data.data(), data.size());
}

void Sha256Hasher::Final(std::string *digest) {
  if (!initialized_) {
    Reset();
  }
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_Final(hash, &ctx_);
  digest->assign(reinterpret_cast<const char*>(hash), SHA256_DIGEST_LENGTH);
  initialized_ = false;
}