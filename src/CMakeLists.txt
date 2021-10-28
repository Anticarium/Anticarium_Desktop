set(TARGET_NAME anticarium_desktop_lib)

set(HEADER_FILES
    anticarium_desktop/Jttp.h
    anticarium_desktop/MainWindowManager.h
    anticarium_desktop/widgets/MainWindow.h
    anticarium_desktop/widgets/RegimeDialog.h
    anticarium_desktop/widgets/DisplayRegimes.h
    anticarium_desktop/DisplayRegimesManager.h
)

set(SOURCE_FILES
    anticarium_desktop/Jttp.cpp
    anticarium_desktop/MainWindowManager.cpp
    anticarium_desktop/widgets/MainWindow.cpp
    anticarium_desktop/widgets/RegimeDialog.cpp
    anticarium_desktop/widgets/DisplayRegimes.cpp
    anticarium_desktop/DisplayRegimesManager.cpp
)

set(FORMS
    anticarium_desktop/widgets/MainWindow.ui
    anticarium_desktop/widgets/RegimeDialog.ui
    anticarium_desktop/widgets/DisplayRegimes.ui
)

include(ExternLibs)
include(FetchContent)

add_library(${TARGET_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
    ${FORMS}
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

ADDQT5CORE(${TARGET_NAME})
ADDQT5WIDGETS(${TARGET_NAME})
ADDQT5NETWORK(${TARGET_NAME})
ADDJSON(${TARGET_NAME})
ADDSHAREDTYPES(${TARGET_NAME})
ADDSPDLOG(${TARGET_NAME})
