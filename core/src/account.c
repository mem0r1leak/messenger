#include <string.h>

#include "core/account.h"
#include "crypto/hash.h"
#include "crypto/sign.h"
#include "shared/base58.h"

result_t account_create(User *u, const char *name, const char *username_prefix) {
    if (strlen(name) > 64) {
        return CORE_ACCOUNT_NAME_TOO_LONG;
    }
    if (strlen(username_prefix) > 16) {
        return CORE_ACCOUNT_PREFIX_TOO_LONG;
    }

    if (identity_generate(u->master_key, u->sk_signature, u->pk_signature, u->sk_encryption, u->pk_encryption) != OK) {
        return CORE_ACCOUNT_CREATE_FAILED;
    }
    memcpy(u->name, name, strlen(name));

    // Building User ID: hash(pk_encryption + pk_signature)
    uint8_t temp[identity_encr_PUBLICKEYBYTES + identity_sign_PUBLICKEYBYTES];
    memcpy(temp, u->pk_encryption, identity_encr_PUBLICKEYBYTES);
    memcpy(temp + identity_encr_PUBLICKEYBYTES, u->pk_signature, identity_sign_PUBLICKEYBYTES);

    cryptohash(u->user_id, temp, identity_encr_PUBLICKEYBYTES + identity_sign_PUBLICKEYBYTES);

    // Building Username
    uint8_t temp2[32];
    size_t prefix_len = strlen(username_prefix);
    memcpy(temp2, username_prefix, prefix_len); // Copying username prefix before '#' symbol

    temp2[prefix_len] = '#'; // The '#' symbol
    memcpy(temp2 + prefix_len + 1, u->user_id, 8); // Copying first 8 bytes of user_id

    uint8_t checksum[hash_BYTES];
    cryptohash(checksum, temp2, prefix_len + 1 + 8);
    memcpy(temp2 + prefix_len + 1 + 8, checksum, 2); // Adding first 2 bytes of hash of username

    uint8_t security_tag[10];
    memcpy(security_tag, temp2 + prefix_len + 1, 10);

    char security_tag_b58[16];
    size_t b58len = 16;
    if (b58enc(security_tag_b58, &b58len, security_tag, 10) == false) { // Encoding security tag in base58
        memset(u, 0, sizeof(User));
        return ENCODING_BASE58_ERR;
    }

    memcpy(u->username, temp2, prefix_len + 1);
    memcpy(u->username + prefix_len + 1, security_tag_b58, strlen(security_tag_b58));

    u->username[prefix_len + 1 + strlen(security_tag_b58)] = '\0';

    // Singing identity
    uint8_t buffer[512] = {0};
    uint8_t hash[signature_BYTES];
    int offest = 0;

    memcpy(buffer, u->user_id, 32);
    offest += 32;
    memcpy(buffer + offest, u->pk_encryption, crypto_box_PUBLICKEYBYTES);
    offest += crypto_box_PUBLICKEYBYTES;
    memcpy(buffer + offest, u->pk_signature, crypto_sign_PUBLICKEYBYTES);
    offest += crypto_sign_PUBLICKEYBYTES;
    memcpy(buffer + offest, u->username, strlen(u->username));
    offest += strlen(u->username);
    memcpy(buffer + offest, name, strlen(name));
    offest += strlen(name);

    cryptohash(hash, buffer, offest);
    cryptosign(u->signature, hash, hash_BYTES, u->sk_signature);

    return OK;
}

result_t account_import(User *u, const uint8_t master_key[32]) {
    if (identity_from_master_key(master_key, u->sk_signature, u->pk_signature, u->sk_encryption, u->pk_encryption) != OK) {
        return CORE_ACCOUNT_IMPORT_FAILED;
    }

    // FOR TESTING ONLY !
    const char *name = "Danylo";
    const char *username_prefix = "danylo";

    memcpy(u->name, name, strlen(name));

    // Building User ID: hash(pk_encryption + pk_signature)
    uint8_t temp[identity_encr_PUBLICKEYBYTES + identity_sign_PUBLICKEYBYTES];
    memcpy(temp, u->pk_encryption, identity_encr_PUBLICKEYBYTES);
    memcpy(temp + identity_encr_PUBLICKEYBYTES, u->pk_signature, identity_sign_PUBLICKEYBYTES);

    cryptohash(u->user_id, temp, identity_encr_PUBLICKEYBYTES + identity_sign_PUBLICKEYBYTES);

    // Building Username
    uint8_t temp2[32];
    size_t prefix_len = strlen(username_prefix);
    memcpy(temp2, username_prefix, prefix_len); // Copying username prefix before '#' symbol

    temp2[prefix_len] = '#'; // The '#' symbol
    memcpy(temp2 + prefix_len + 1, u->user_id, 8); // Copying first 8 bytes of user_id

    uint8_t checksum[hash_BYTES];
    cryptohash(checksum, temp2, prefix_len + 1 + 8);
    memcpy(temp2 + prefix_len + 1 + 8, checksum, 2); // Adding first 2 bytes of hash of username

    uint8_t security_tag[10];
    memcpy(security_tag, temp2 + prefix_len + 1, 10);

    char security_tag_b58[16];
    size_t b58len = 16;
    if (b58enc(security_tag_b58, &b58len, security_tag, 10) == false) { // Encoding security tag in base58
        return ENCODING_BASE58_ERR;
    }

    memcpy(u->username, temp2, prefix_len + 1);
    memcpy(u->username + prefix_len + 1, security_tag_b58, strlen(security_tag_b58));

    u->username[prefix_len + 1 + strlen(security_tag_b58)] = '\0';

    // Singing identity
    uint8_t buffer[512] = {0};
    uint8_t hash[signature_BYTES];
    int offest = 0;

    memcpy(buffer, u->user_id, 32);
    offest += 32;
    memcpy(buffer + offest, u->pk_encryption, crypto_box_PUBLICKEYBYTES);
    offest += crypto_box_PUBLICKEYBYTES;
    memcpy(buffer + offest, u->pk_signature, crypto_sign_PUBLICKEYBYTES);
    offest += crypto_sign_PUBLICKEYBYTES;
    memcpy(buffer + offest, u->username, strlen(u->username));
    offest += strlen(u->username);
    memcpy(buffer + offest, name, strlen(name));
    offest += strlen(name);

    cryptohash(hash, buffer, offest);
    cryptosign(u->signature, hash, hash_BYTES, u->sk_signature);

    return OK;
}

result_t account_verify(User *u) {
    uint8_t buffer[512] = {0};
    uint8_t hash[signature_BYTES];
    int offest = 0;

    memcpy(buffer, u->user_id, 32);
    offest += 32;
    memcpy(buffer + offest, u->pk_encryption, crypto_box_PUBLICKEYBYTES);
    offest += crypto_box_PUBLICKEYBYTES;
    memcpy(buffer + offest, u->pk_signature, crypto_sign_PUBLICKEYBYTES);
    offest += crypto_sign_PUBLICKEYBYTES;
    memcpy(buffer + offest, u->username, strlen(u->username));
    offest += strlen(u->username);
    memcpy(buffer + offest, u->name, strlen(u->name));
    offest += strlen(u->name);

    cryptohash(hash, buffer, offest);

    if (crypto_sign_verify(u->signature, hash, hash_BYTES, u->pk_signature) == CRYPTO_INVALID_SIGNATURE) {
        return CORE_ACCOUNT_INVALID;
    }

    return OK;
}
