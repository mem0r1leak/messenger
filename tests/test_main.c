#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "core/test_account.c"
#include "crypto/test_sign.c"

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_account_create),
        cmocka_unit_test(test_account_import),
        cmocka_unit_test(test_sign),
        cmocka_unit_test(test_account_verify),
        cmocka_unit_test(test_account_username_verify_integrity),
        cmocka_unit_test(test_account_username_verify_authenticity)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
