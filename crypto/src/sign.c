#include "crypto/sign.h"
#include "shared/result.h"

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

result_t crypto_sign_verify(
    const uint8_t signature[signature_BYTES], const uint8_t *message,
    unsigned long long message_len, const uint8_t pk[identity_sign_PUBLICKEYBYTES]
){
    if (sodium_init() < 0) {
        return CRYPTO_ERR;
    }

    if (crypto_sign_verify_detached(signature, message, message_len, pk) == -1) {
        return CRYPTO_INVALID_SIGNATURE;
    }

    return OK;
}
