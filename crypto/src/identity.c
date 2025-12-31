#include <sodium/crypto_box.h>
#include <sodium/crypto_hash_sha256.h>
#include <sodium/crypto_sign.h>
#include <sodium/randombytes.h>
#include <stdbool.h>
#include <stddef.h>

#include "crypto/identity.h"

result_t identity_generate(
    uint8_t master_key[identity_MASTERKEYBYTES],
    uint8_t sk_signature[identity_sign_SECRETKEYBYTES],
    uint8_t pk_signature[identity_sign_PUBLICKEYBYTES],
    uint8_t sk_encryption[identity_encr_SECRETKEYBYTES],
    uint8_t pk_encryption[identity_encr_PUBLICKEYBYTES]
){
    if (sodium_init() < 0) {
        return CRYPTO_ERR;
    }

    randombytes_buf(master_key, crypto_box_SEEDBYTES);
    crypto_sign_seed_keypair(pk_signature, sk_signature, master_key);
    crypto_box_seed_keypair(pk_encryption, sk_encryption, master_key);

    return OK;
}

result_t identity_from_master_key(
    const uint8_t master_key[identity_MASTERKEYBYTES],
    uint8_t sk_signature[identity_sign_SECRETKEYBYTES],
    uint8_t pk_signature[identity_sign_PUBLICKEYBYTES],
    uint8_t sk_encryption[identity_encr_SECRETKEYBYTES],
    uint8_t pk_encryption[identity_encr_PUBLICKEYBYTES]
){
    if (sodium_init() < 0) {
        return CRYPTO_ERR;
    }

    crypto_sign_seed_keypair(pk_signature, sk_signature, master_key);
    crypto_box_seed_keypair(pk_encryption, sk_encryption, master_key);

    return OK;
}
