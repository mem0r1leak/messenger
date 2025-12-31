add_executable(messenger_tests
    test_main.c
    core/test_account.c
)

find_package(cmocka REQUIRED)

target_link_libraries(messenger_tests
    PRIVATE
        messenger_core
        messenger_shared
        messenger_crypto
        cmocka
)

add_test(NAME messenger_tests COMMAND messenger_tests)
