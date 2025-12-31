#pragma once

#include <sodium/crypto_box.h>
#include <sodium/crypto_hash_sha256.h>
#include <sodium/crypto_sign.h>
#include <stdint.h>
#include <sodium.h>

#include "shared/result.h"

#define identity_MASTERKEYBYTES crypto_box_SEEDBYTES
#define identity_sign_SECRETKEYBYTES crypto_sign_SECRETKEYBYTES
#define identity_sign_PUBLICKEYBYTES crypto_sign_PUBLICKEYBYTES
#define identity_encr_SECRETKEYBYTES crypto_box_SECRETKEYBYTES
#define identity_encr_PUBLICKEYBYTES crypto_box_PUBLICKEYBYTES

result_t identity_generate(
    uint8_t master_key[identity_MASTERKEYBYTES],
    uint8_t sk_signature[identity_sign_SECRETKEYBYTES],
    uint8_t pk_signature[identity_sign_PUBLICKEYBYTES],
    uint8_t sk_encryption[identity_encr_SECRETKEYBYTES],
    uint8_t pk_encryption[identity_encr_PUBLICKEYBYTES]
);

result_t identity_from_master_key(
    const uint8_t master_key[identity_MASTERKEYBYTES],
    uint8_t sk_signature[identity_sign_SECRETKEYBYTES],
    uint8_t pk_signature[identity_sign_PUBLICKEYBYTES],
    uint8_t sk_encryption[identity_encr_SECRETKEYBYTES],
    uint8_t pk_encryption[identity_encr_PUBLICKEYBYTES]
);
