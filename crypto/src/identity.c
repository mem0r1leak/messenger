#include "../include/identity.h"
#include "../../shared/encoding/base58.h"

#include <sodium/crypto_box.h>
#include <sodium/crypto_hash_sha256.h>
#include <sodium/crypto_sign.h>
#include <sodium/randombytes.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

result_t identity_generate(
    uint8_t master_key[crypto_box_SEEDBYTES],
    uint8_t sk_signature[crypto_sign_SECRETKEYBYTES],
    uint8_t pk_signature[crypto_sign_PUBLICKEYBYTES],
    uint8_t sk_encryption[crypto_box_SECRETKEYBYTES],
    uint8_t pk_encryption[crypto_box_PUBLICKEYBYTES],
    uint8_t user_id[crypto_hash_sha256_BYTES]
){
    if (sodium_init() < 0) {
        return CRYPTO_ERR;
    }

    randombytes_buf(master_key, crypto_box_SEEDBYTES);
    crypto_sign_seed_keypair(pk_signature, sk_signature, master_key);
    crypto_box_seed_keypair(pk_encryption, sk_encryption, master_key);

    uint8_t temp[crypto_sign_PUBLICKEYBYTES + crypto_box_PUBLICKEYBYTES];
    memcpy(temp, pk_encryption, crypto_box_PUBLICKEYBYTES);
    memcpy(temp + crypto_box_PUBLICKEYBYTES, pk_signature, crypto_sign_PUBLICKEYBYTES);

    crypto_hash_sha256(user_id, temp, crypto_sign_PUBLICKEYBYTES + crypto_box_PUBLICKEYBYTES);

    return OK;
}

result_t identity_from_master_key(
    const uint8_t master_key[crypto_box_SEEDBYTES],
    uint8_t sk_signature[crypto_sign_SECRETKEYBYTES],
    uint8_t pk_signature[crypto_sign_PUBLICKEYBYTES],
    uint8_t sk_encryption[crypto_box_SECRETKEYBYTES],
    uint8_t pk_encryption[crypto_box_PUBLICKEYBYTES],
    uint8_t user_id[crypto_hash_sha256_BYTES]
){
    if (sodium_init() < 0) {
        return CRYPTO_ERR;
    }

    crypto_sign_seed_keypair(pk_signature, sk_signature, master_key);
    crypto_box_seed_keypair(pk_encryption, sk_encryption, master_key);

    uint8_t temp[crypto_sign_PUBLICKEYBYTES + crypto_box_PUBLICKEYBYTES];
    memcpy(temp, pk_encryption, crypto_box_PUBLICKEYBYTES);
    memcpy(temp + crypto_box_PUBLICKEYBYTES, pk_signature, crypto_sign_PUBLICKEYBYTES);

    crypto_hash_sha256(user_id, temp, crypto_sign_PUBLICKEYBYTES + crypto_box_PUBLICKEYBYTES);

    return OK;
}

result_t identity_get_username(
    const uint8_t user_id[crypto_hash_sha256_BYTES],
    const char username_prefix[16],
    char username[32]
){
    if (sodium_init() < 0) {
        return CRYPTO_ERR;
    }

    uint8_t temp[32];
    size_t prefix_len = strlen(username_prefix);
    memcpy(temp, username_prefix, prefix_len); // Copying username prefix before '#' symbol

    temp[prefix_len] = '#'; // The '#' symbol
    memcpy(temp + prefix_len + 1, user_id, 8); // Copying first 8 bytes of user_id

    uint8_t checksum[crypto_hash_sha256_BYTES];
    crypto_hash_sha256(checksum, temp, prefix_len + 1 + 8);
    memcpy(temp + prefix_len + 1 + 8, checksum, 2); // Adding first 2 bytes of hash of username

    uint8_t security_tag[10];
    memcpy(security_tag, temp + prefix_len + 1, 10);

    char security_tag_b58[16];
    size_t b58len = 16;
    if (b58enc(security_tag_b58, &b58len, security_tag, 10) == false) {
        return ENCODING_BASE58_ERR;
    }

    memcpy(username, temp, prefix_len + 1);
    memcpy(username + prefix_len + 1, security_tag_b58, strlen(security_tag_b58));

    username[prefix_len + 1 + strlen(security_tag_b58)] = '\0';

    return OK;
}

result_t identity_sign(
    const char name[64],
    const char username[32],
    const uint8_t user_id[32],
    const uint8_t pk_signature[crypto_sign_PUBLICKEYBYTES],
    const uint8_t pk_encryption[crypto_box_PUBLICKEYBYTES],
    const uint8_t sk_signature[crypto_sign_SECRETKEYBYTES],
    uint8_t signature[crypto_sign_BYTES]
){
    if (sodium_init() < 0) {
        return CRYPTO_ERR;
    }

    uint8_t buffer[512] = {0};
    uint8_t hash[crypto_hash_sha256_BYTES];
    unsigned long long siglen_p = 0;
    int offest = 0;

    memcpy(buffer, user_id, 32);
    offest += 32;
    memcpy(buffer + offest, pk_encryption, crypto_box_PUBLICKEYBYTES);
    offest += crypto_box_PUBLICKEYBYTES;
    memcpy(buffer + offest, pk_signature, crypto_sign_PUBLICKEYBYTES);
    offest += crypto_sign_PUBLICKEYBYTES;
    memcpy(buffer + offest, username, strlen(username));
    offest += strlen(username);
    memcpy(buffer + offest, name, strlen(name));
    offest += strlen(name);

    crypto_hash_sha256(hash, buffer, offest);
    crypto_sign_detached(signature, &siglen_p, hash, crypto_hash_sha256_BYTES, sk_signature);

    return OK;
}
