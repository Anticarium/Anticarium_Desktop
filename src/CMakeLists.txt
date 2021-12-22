set(TARGET_NAME anticarium_desktop_lib)

set(HEADER_FILES
    anticarium_desktop/Jttp.h
    anticarium_desktop/MainWindowManager.h
    anticarium_desktop/widgets/MainWindow.h
    anticarium_desktop/widgets/RegimeDialog.h
    anticarium_desktop/widgets/DisplayRegimes.h
    anticarium_desktop/DisplayRegimesManager.h
    anticarium_desktop/config/ApplicationSettings.h
    anticarium_desktop/VideoManager.h
    anticarium_desktop/UDPReader.h
    anticarium_desktop/RowBuilder.h
    anticarium_desktop/config/ImageRow.hpp
    anticarium_desktop/ImageProcessor.h
)

set(SOURCE_FILES
    anticarium_desktop/Jttp.cpp
    anticarium_desktop/MainWindowManager.cpp
    anticarium_desktop/widgets/MainWindow.cpp
    anticarium_desktop/widgets/RegimeDialog.cpp
    anticarium_desktop/widgets/DisplayRegimes.cpp
    anticarium_desktop/DisplayRegimesManager.cpp
    anticarium_desktop/config/ApplicationSettings.cpp
    anticarium_desktop/VideoManager.cpp
    anticarium_desktop/UDPReader.cpp
    anticarium_desktop/RowBuilder.cpp
    anticarium_desktop/ImageProcessor.cpp
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
