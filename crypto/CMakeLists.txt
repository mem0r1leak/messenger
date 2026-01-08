add_library(messenger_crypto
    src/identity.c
    src/hash.c
    src/sign.c
)

target_include_directories(messenger_crypto
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)

target_link_libraries(messenger_crypto
    PRIVATE
        ${SODIUM_LIBRARIES}
        messenger_shared
)

target_compile_options(messenger_crypto PRIVATE -Wall -Wextra -Werror)
