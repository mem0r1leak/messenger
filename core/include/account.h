#pragma once

#include <stdint.h>
#include "../../shared/result.h"

typedef struct {
    char name[64];
    char username[32]; // 16 + 1 + 14 + '\0'
    uint8_t user_id[32];
    uint8_t master_key[32];
    uint8_t sk_signature[64];
    uint8_t pk_signature[32];
    uint8_t sk_encryption[32];
    uint8_t pk_encryption[32];
    uint8_t signature[64];
} User;

result_t account_create(User *u, const char name[64], const char username_prefix[16]);
result_t account_import(User *u, const uint8_t master_key[32]);
