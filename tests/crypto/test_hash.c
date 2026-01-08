#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "crypto/hash.h"
#include "shared/result.h"

static void test_hash() {
    const char *message = "1234";

    const uint8_t expected_hash[hash_BYTES] = {
        0x03, 0xac, 0x67, 0x42, 0x16, 0xf3, 0xe1, 0x5c,
        0x76, 0x1e, 0xe1, 0xa5, 0xe2, 0x55, 0xf0, 0x67,
        0x95, 0x36, 0x23, 0xc8, 0xb3, 0x88, 0xb4, 0x45,
        0x9e, 0x13, 0xf9, 0x78, 0xd7, 0xc8, 0x46, 0xf4
    };

    uint8_t hash[hash_BYTES];
    result_t r = cryptohash(hash, (const uint8_t*)message, strlen(message));

    assert_int_equal(r, OK);
    assert_memory_equal(hash, expected_hash, hash_BYTES);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_hash)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
