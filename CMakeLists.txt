cmake_minimum_required(VERSION 3.16)

project(ad_logger
    VERSION 1.0
    LANGUAGES C CXX
)

# ---- C STANDARD ----
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ---- AD_LOGGER TARGET ----
add_library(ad_logger SHARED
    src/ad_logger.c
)

# ---- PUBLIC / PRIVATE HEADERS ----
target_include_directories(ad_logger
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../prebuilt/inih/include
)

# ---- PREBUILT ZLOG (IMPORTED TARGET) ----
add_library(zlog SHARED IMPORTED)

set_target_properties(zlog PROPERTIES
    IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/../../prebuilt/zlog/lib/libzlog.so
    INTERFACE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/../../prebuilt/zlog/include
)

# ---- LINK DEPENDENCIES ----
target_link_libraries(ad_logger
    PUBLIC zlog
)

# ---- TESTS ----
enable_testing()
add_subdirectory(tests)
