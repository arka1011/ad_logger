cmake_minimum_required(VERSION 3.16)

project(ad_logger
    VERSION 1.0
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(AD_LOGGER_SOURCES
    src/ad_logger.c
)

# ---- CREATE THE TARGET FIRST ----
add_library(ad_logger SHARED ${AD_LOGGER_SOURCES})

# ---- ADD INCLUDE DIRS ----
target_include_directories(ad_logger PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../prebuilt/inih/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../prebuilt/zlog/include
)

# ---- LINK LIBRARIES ----
target_link_libraries(ad_logger
    ${CMAKE_CURRENT_SOURCE_DIR}/../../prebuilt/zlog/lib/libzlog.so
)

enable_testing()
add_subdirectory(tests)

