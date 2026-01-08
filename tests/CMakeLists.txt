find_package(cmocka REQUIRED)

function(add_messenger_test name source)
    add_executable(${name} ${source})
    target_link_libraries(${name}
        messenger_core
        messenger_shared
        messenger_crypto
        cmocka
    )
    add_test(NAME ${name} COMMAND ${name})
endfunction()

add_messenger_test(
    test_account_create
    core/test_account_create.c
)
