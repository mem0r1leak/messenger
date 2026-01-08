#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "core/account.h"
#include "shared/result.h"

static void test_account_create_valid() {
    User u = {0};

    const char *name = "Alice";
    const char *prefix = "alice";

    result_t r = account_create(&u, name, prefix);

    print_message("\nName:          %s\n", u.name);
    print_message("Username:      %s\n", u.username);
    print_message("User ID:       ");
    for (int i = 0; i < 32; i++) {
        print_message("%02x", u.user_id[i]);
    }
    print_message("\nsk_signature:  ");
    for (int i = 0; i < 64; i++) {
        print_message("%02x", u.sk_signature[i]);
    }
    print_message("\npk_signature:  ");
    for (int i = 0; i < 32; i++) {
        print_message("%02x", u.pk_signature[i]);
    }
    print_message("\nsk_encryption: ");
    for (int i = 0; i < 32; i++) {
        print_message("%02x", u.sk_encryption[i]);
    }
    print_message("\npk_encryption: ");
    for (int i = 0; i < 32; i++) {
        print_message("%02x", u.pk_encryption[i]);
    }
    print_message("\nMaster Key:    ");
    for (int i = 0; i < 32; i++) {
        print_message("%02x", u.master_key[i]);
    }
    print_message("\nSignature:     ");
    for (int i = 0; i < 64; i++) {
        print_message("%02x", u.signature[i]);
    }
    print_message("\n\n");

    assert_int_equal(r, OK);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_account_create_valid),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
