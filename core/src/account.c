#include "../include/account.h"
#include "../../shared/result.h"
#include "../../crypto/include/identity.h"
#include <string.h>

result_t account_create(User *u, const char name[64], const char username_prefix[16]) {
    if (identity_generate(u->master_key, u->sk_signature, u->pk_signature, u->sk_encryption, u->pk_encryption, u->user_id) != OK) {
        return CORE_ACCOUNT_CREATE_FAILED;
    }

    if (identity_get_username(u->user_id, username_prefix, u->username) != OK) {
        return CORE_ACCOUNT_CREATE_FAILED;
    }

    if (identity_sign(name, u->username, u->user_id, u->pk_signature, u->pk_encryption, u->sk_signature, u->signature) != OK) {
        return CORE_ACCOUNT_CREATE_FAILED;
    }
    memcpy(u->name, name, strlen(name));

    return OK;
}

result_t account_import(User *u, const uint8_t master_key[32]) {
    if (identity_from_master_key(master_key, u->sk_signature, u->pk_signature, u->sk_encryption, u->pk_encryption, u->user_id) != OK) {
        return CORE_ACCOUNT_IMPORT_FAILED;
    }

    // FOR TESTING ONLY !
    const char *name = "Danylo";
    const char *username_prefix = "danylo";

    if (identity_get_username(u->user_id, username_prefix, u->username) != OK) {
        return CORE_ACCOUNT_CREATE_FAILED;
    }

    if (identity_sign(name, u->username, u->user_id, u->pk_signature, u->pk_encryption, u->sk_signature, u->signature) != OK) {
        return CORE_ACCOUNT_CREATE_FAILED;
    }
    memcpy(u->name, name, strlen(name));

    return OK;
}
