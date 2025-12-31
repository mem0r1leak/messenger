#pragma once

#include <stddef.h>
#include <stdint.h>
#include <sodium/crypto_hash_sha256.h>

#include "shared/result.h"

#define hash_BYTES crypto_hash_sha256_BYTES

result_t cryptohash(uint8_t *out, const uint8_t *in, const size_t in_len);
