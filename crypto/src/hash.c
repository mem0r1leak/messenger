#include <sodium/crypto_hash_sha256.h>
#include <sodium/core.h>

#include "crypto/hash.h"

result_t cryptohash(uint8_t *out, const uint8_t *in, const size_t in_len) {
    if (sodium_init() < 0) {
        return CRYPTO_ERR;
    }

    crypto_hash_sha256(out, in, in_len);
    return OK;
}
