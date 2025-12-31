#include "crypto/sign.h"

result_t cryptosign(
    uint8_t signature[signature_BYTES], const uint8_t *message, unsigned long long message_len,
    const uint8_t sk[identity_sign_SECRETKEYBYTES]
){
    if (sodium_init() < 0) {
        return CRYPTO_ERR;
    }

    crypto_sign_detached(signature, NULL, message, message_len, sk);

    return OK;
}
