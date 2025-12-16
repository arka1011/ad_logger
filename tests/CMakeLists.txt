# ---- TEST EXECUTABLE ----
add_executable(ad_logger_tests
    test_main.cpp
    test_logger.cpp
)

# ---- LINK AGAINST LIBRARY UNDER TEST ----
target_link_libraries(ad_logger_tests PRIVATE
    ad_logger
)

# ---- GOOGLE TEST (IMPORTED) ----
add_library(gtest STATIC IMPORTED)
set_target_properties(gtest PROPERTIES
    IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../prebuilt/googletest/build/lib/libgtest.a
    INTERFACE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../prebuilt/googletest/googletest/include
)

add_library(gtest_main STATIC IMPORTED)
set_target_properties(gtest_main PROPERTIES
    IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../prebuilt/googletest/build/lib/libgtest_main.a
)

# ---- LINK TEST FRAMEWORK ----
target_link_libraries(ad_logger_tests PRIVATE
    gtest
    gtest_main
    pthread
)

# ---- REGISTER TEST ----
add_test(NAME ad_logger_tests COMMAND ad_logger_tests)

# ---- COPY CONFIG FILES ----
file(GLOB CONFIG_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/../test_configs/*
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/configs)

foreach(CONFIG_FILE ${CONFIG_FILES})
    get_filename_component(CONFIG_NAME ${CONFIG_FILE} NAME)

    configure_file(
        ${CONFIG_FILE}
        ${CMAKE_CURRENT_BINARY_DIR}/configs/${CONFIG_NAME}
        COPYONLY
    )
endforeach()


