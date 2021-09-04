include(ExternLibs)
set(TARGET_NAME anticarium_desktop_lib)

set(HEADER_FILES
    anticarium_desktop/jttp.h
    anticarium_desktop/widgets/hometab.h
    anticarium_desktop/widgets/modestab.h
    anticarium_desktop/widgets/usertab.h
    anticarium_desktop/widgets/mainwindow.h
    anticarium_desktop/custom_elements/clickablewidget.h
)

set(SOURCE_FILES
    anticarium_desktop/jttp.cpp
    anticarium_desktop/widgets/hometab.cpp
    anticarium_desktop/widgets/modestab.cpp
    anticarium_desktop/widgets/usertab.cpp
    anticarium_desktop/widgets/mainwindow.cpp
    anticarium_desktop/custom_elements/clickablewidget.cpp
)

set(FORMS
    anticarium_desktop/widgets/hometab.ui
    anticarium_desktop/widgets/modestab.ui
    anticarium_desktop/widgets/usertab.ui
    anticarium_desktop/widgets/mainwindow.ui
)

add_library(${TARGET_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
    ${FORMS}
    anticarium_desktop/resources.qrc
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/anticarium_desktop)

ADDQT6CORE(${TARGET_NAME})
ADDQT6WIDGETS(${TARGET_NAME})
ADDQT6NETWORK(${TARGET_NAME})
ADDJSON(${TARGET_NAME})

