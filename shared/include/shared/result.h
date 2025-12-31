#pragma once

typedef enum {
    OK = 0,

    // Shared
    ENCODING_BASE58_ERR,

    // Core
    CORE_ACCOUNT_CREATE_FAILED,
    CORE_ACCOUNT_IMPORT_FAILED,
    CORE_ACCOUNT_NAME_TOO_LONG,
    CORE_ACCOUNT_PREFIX_TOO_LONG,

    // Crypto
    CRYPTO_ERR,
    CRYPTO_AUTH_FAILED,
} result_t;
