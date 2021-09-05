set(TARGET_NAME anticarium_desktop_lib)

set(HEADER_FILES
    anticarium_desktop/Jttp.h
    anticarium_desktop/MainWindowManager.h
    anticarium_desktop/widgets/MainWindow.h
)

set(SOURCE_FILES
    anticarium_desktop/Jttp.cpp
    anticarium_desktop/MainWindowManager.cpp
    anticarium_desktop/widgets/MainWindow.cpp
)

set(FORMS
    anticarium_desktop/widgets/MainWindow.ui
)

include(ExternLibs)
include(FetchContent)

add_library(${TARGET_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
    ${FORMS}
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/anticarium_desktop)

ADDQT6CORE(${TARGET_NAME})
ADDQT6WIDGETS(${TARGET_NAME})
ADDQT6NETWORK(${TARGET_NAME})
ADDJSON(${TARGET_NAME})
ADDSHAREDTYPES(${TARGET_NAME})

