#pragma once

#include <stdint.h>
#include <sodium/crypto_sign.h>

#include "identity.h"
#include "shared/result.h"

#define signature_BYTES crypto_sign_BYTES

result_t cryptosign(
    uint8_t signature[signature_BYTES], const uint8_t *message, unsigned long long message_len,
    const uint8_t sk[identity_sign_SECRETKEYBYTES]
);
