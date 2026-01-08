#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "core/account.h"
#include "shared/result.h"

static void test_username_verify_integrity_ok() {
    const char *username = "alice#DGfAX29q1dhytj";
    result_t r = account_username_verify_integrity(username);

    assert_int_equal(r, OK);
}

static void test_username_verify_integrity_null_username() {
    const char *username = NULL;
    result_t r = account_username_verify_integrity(username);

    assert_int_equal(r, CORE_ACCOUNT_USERNAME_CORRUPTED);
}

static void test_username_verify_integrity_invalid_size() {
    const char *username_long = "alice#DGfAX29q1dhytjooooooooooooooooo";
    const char *username_empty = "";

    result_t r_long = account_username_verify_integrity(username_long);
    result_t r_empty = account_username_verify_integrity(username_empty);

    assert_int_equal(r_long, CORE_ACCOUNT_USERNAME_INVALID_SIZE);
    assert_int_equal(r_empty, CORE_ACCOUNT_USERNAME_INVALID_SIZE);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_username_verify_integrity_ok),
        cmocka_unit_test(test_username_verify_integrity_null_username),
        cmocka_unit_test(test_username_verify_integrity_invalid_size)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
