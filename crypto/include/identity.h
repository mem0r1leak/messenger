#pragma once

#include <sodium/crypto_box.h>
#include <sodium/crypto_hash_sha256.h>
#include <sodium/crypto_sign.h>
#include <stdint.h>
#include <sodium.h>
#include "../../shared/result.h"

result_t identity_generate(
    uint8_t master_key[crypto_box_SEEDBYTES],
    uint8_t sk_signature[crypto_sign_SECRETKEYBYTES],
    uint8_t pk_signature[crypto_sign_PUBLICKEYBYTES],
    uint8_t sk_encryption[crypto_box_SECRETKEYBYTES],
    uint8_t pk_encryption[crypto_box_PUBLICKEYBYTES],
    uint8_t user_id[crypto_hash_sha256_BYTES]
);

result_t identity_from_master_key(
    const uint8_t master_key[crypto_box_SEEDBYTES],
    uint8_t sk_signature[crypto_sign_SECRETKEYBYTES],
    uint8_t pk_signature[crypto_sign_PUBLICKEYBYTES],
    uint8_t sk_encryption[crypto_box_SECRETKEYBYTES],
    uint8_t pk_encryption[crypto_box_PUBLICKEYBYTES],
    uint8_t user_id[crypto_hash_sha256_BYTES]
);

result_t identity_get_username(
    const uint8_t user_id[crypto_hash_sha256_BYTES],
    const char username_prefix[16],
    char username[32]
);

result_t identity_sign(
    const char name[64],
    const char username[32],
    const uint8_t user_id[32],
    const uint8_t pk_signature[crypto_sign_PUBLICKEYBYTES],
    const uint8_t pk_encryption[crypto_box_PUBLICKEYBYTES],
    const uint8_t sk_signature[crypto_sign_SECRETKEYBYTES],
    uint8_t signature[crypto_sign_BYTES]
);
