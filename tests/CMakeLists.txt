include(ExternLibs)
include(GoogleTest)

set(TARGET_NAME anticarium_desktop_tests)
set(TEST_DATA_DIR_HEADER_PATH ${CMAKE_BINARY_DIR}/tests/include/anticarium_desktop_tests)

set(SOURCE_FILES
    main.cpp
    config/ApplicationSettingsTests.cpp
    ImageBuilderTests.cpp
)

add_executable(${TARGET_NAME}
    ${SOURCE_FILES}
)

configure_file(TestDataDirectory.h.in  ${TEST_DATA_DIR_HEADER_PATH}/TestDataDirectory.h)

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${TEST_DATA_DIR_HEADER_PATH}
    ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${TARGET_NAME} PRIVATE anticarium_desktop_lib)

ADDGTEST(${TARGET_NAME})
ADDQT5CORE(${TARGET_NAME})
ADDSPDLOG(${TARGET_NAME})
ADDQT5WIDGETS(${TARGET_NAME})
