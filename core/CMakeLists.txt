add_library(messenger_core
    src/account.c
)

target_include_directories(messenger_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(messenger_core
    PRIVATE
        messenger_crypto
        messenger_shared
)

target_compile_options(messenger_core PRIVATE -Wall -Wextra -Werror)
