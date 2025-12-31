#pragma once

#include <stdint.h>

#include "shared/result.h"
#include "crypto/identity.h"
#include "crypto/sign.h"

#define account_NAMEBYTES 64
#define account_USERIDBYTES 32
#define account_USERNAMEBYTES 32 // 16 + 1 + 14 + '\0'

typedef struct {
    char name[account_NAMEBYTES];
    char username[account_USERNAMEBYTES];
    uint8_t user_id[account_USERIDBYTES];
    uint8_t master_key[identity_MASTERKEYBYTES];
    uint8_t sk_signature[identity_sign_SECRETKEYBYTES];
    uint8_t pk_signature[identity_sign_PUBLICKEYBYTES];
    uint8_t sk_encryption[identity_encr_SECRETKEYBYTES];
    uint8_t pk_encryption[identity_encr_PUBLICKEYBYTES];
    uint8_t signature[signature_BYTES];
} User;

result_t account_create(User *u, const char *name, const char *username_prefix);
result_t account_import(User *u, const uint8_t master_key[32]);
