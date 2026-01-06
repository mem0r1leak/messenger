#pragma once

#include <stdint.h>

#include "shared/result.h"
#include "crypto/identity.h"
#include "crypto/sign.h"

// Username constants
#define PREFIX_MIN_LEN            1
#define PREFIX_MAX_LEN            16
#define USERNAME_MAX_LEN          31

#define SECURITY_TAG_BIN_LEN      10
#define SECURITY_TAG_STR_MAX_LEN  14
#define SECURITY_TAG_DATA_LEN     8
#define SECURITY_TAG_CHECK_LEN    2

// Account constants
#define account_NAMEBYTES         64
#define account_USERIDBYTES       32
#define account_USERNAMEBYTES     PREFIX_MAX_LEN + 1 + SECURITY_TAG_STR_MAX_LEN + 1         // 16 + 1 + 14 + '\0'

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
result_t account_username_verify_integrity(const char *username);
result_t account_username_verify_authenticity(const char *username, const uint8_t user_id[account_USERIDBYTES]);
result_t account_verify(User *u);
