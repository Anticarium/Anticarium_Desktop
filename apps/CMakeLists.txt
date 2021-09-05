set(TARGET_NAME anticarium_desktop_app)

include(ExternLibs)
include(FetchContent)

add_executable(${TARGET_NAME}
    main.cpp
    ${CMAKE_SOURCE_DIR}/src/anticarium_desktop/Resources.qrc
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/anticarium_desktop)
target_link_libraries(${TARGET_NAME} PRIVATE anticarium_desktop_lib)
ADDQT6CORE(${TARGET_NAME})
ADDQT6WIDGETS(${TARGET_NAME})
ADDQT6NETWORK(${TARGET_NAME})
ADDJSON(${TARGET_NAME})
ADDSHAREDTYPES(${TARGET_NAME})
