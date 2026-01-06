#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "core/account.h"
#include "shared/result.h"

static void test_account_create() {
    User u = {0};
    User u2 = {0};

    const char *name = "Danylo";
    const char *prefix = "danyloxx";

    result_t res = account_create(&u, name, prefix);
    result_t res2 = account_create(&u2, name, prefix);

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

    assert_int_equal(res, OK);
    assert_int_equal(res2, OK);
    assert_memory_not_equal(u.user_id, u2.user_id, account_USERIDBYTES);
}

static void test_account_import(void **state) {
    (void) state;
    User u1 = {0};
    User u2 = {0};

    const uint8_t master_key[32] = {
        0x3a, 0x2e, 0x14, 0xb5, 0xa9, 0x52, 0x6d, 0x62,
        0xe5, 0x7a, 0x89, 0x5e, 0x91, 0x7e, 0xf9, 0x35,
        0xfa, 0x8a, 0xf3, 0x53, 0x8e, 0x0b, 0x2d, 0xbd,
        0x4a, 0xb5, 0x49, 0xc6, 0x5a, 0x98, 0x68, 0xa3
    };

    result_t res1 = account_import(&u1, master_key);
    result_t res2 = account_import(&u2, master_key);

    assert_int_equal(res1, OK);
    assert_int_equal(res2, OK);
    assert_memory_equal(u1.user_id, u2.user_id, account_USERIDBYTES);
}

static void test_account_verify() {
    User u_valid = {0};
    User u_invalid = {0};

    const char *name = "Alice";
    const char *prefix = "alice";

    account_create(&u_valid, name, prefix);
    account_create(&u_invalid, name, prefix);

    // It makes signature invalid
    u_invalid.signature[8] = 0xd9;
    u_invalid.signature[2] = 0x04;
    u_invalid.signature[36] = 0xf6;

    result_t res1 = account_verify(&u_valid);
    result_t res2 = account_verify(&u_invalid);

    assert_int_equal(res1, OK);
    assert_int_equal(res2, CORE_ACCOUNT_INVALID);
}

static void test_account_username_verify_integrity() {
    const char *username_valid = "danyloxx#5n5WbNAMXjrcYS";
    const char *username_corrupted = "daanyloxx#5n5WbNAMXjrcYS";

    result_t valid = account_username_verify_integrity(username_valid);
    result_t corrupted = account_username_verify_integrity(username_corrupted);

    assert_int_equal(valid, OK);
    assert_int_not_equal(corrupted, OK);
}

static void test_account_username_verify_authenticity() {
    User u = {0};

    const char *name = "Danylo";
    const char *prefix = "danyloxx";

    account_create(&u, name, prefix);

    result_t ok = account_username_verify_authenticity(u.username, u.user_id);
    u.user_id[19] = 0xdf;
    u.user_id[3] = 0xa1;
    result_t fail = account_username_verify_authenticity(u.username, u.user_id);

    assert_int_equal(ok, OK);
    assert_int_equal(fail, CORE_ACCOUNT_USERNAME_FORGED);
}
