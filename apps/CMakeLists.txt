set(TARGET_NAME anticarium_desktop_app)

include(ExternLibs)
include(FetchContent)

add_executable(${TARGET_NAME}
    WIN32
    main.cpp
    ${CMAKE_SOURCE_DIR}/src/anticarium_desktop/Resources.qrc
    ${CMAKE_SOURCE_DIR}/src/anticarium_desktop/WindowsResources.rc
)

configure_file(${CMAKE_SOURCE_DIR}/settings.ini.in settings.ini)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${TARGET_NAME} PRIVATE anticarium_desktop_lib)
ADDQT5CORE(${TARGET_NAME})
ADDQT5WIDGETS(${TARGET_NAME})
ADDQT5NETWORK(${TARGET_NAME})
ADDJSON(${TARGET_NAME})
ADDSHAREDTYPES(${TARGET_NAME})
ADDSPDLOG(${TARGET_NAME})
