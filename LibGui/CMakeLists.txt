cmake_minimum_required(VERSION 3.16)

project(NaiSys-Gui VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++17 -stdlib=libc++")
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(GUI_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qml/)
set(GUI_COMPONENTS_DIR qml/components)
set(GUI_LAYOUTS_DIR qml/layouts)
set(GUI_PLUGINS_DIR src/)
set(GUI_ICONS_DIR icons/)

find_package(Qt6 6.2 COMPONENTS Quick Core Gui Widgets REQUIRED)

set( COMPONENT_FILES
    ${GUI_COMPONENTS_DIR}/NaiSysAbstractPopup.qml
    ${GUI_COMPONENTS_DIR}/NaiSysAbstractView.qml
    ${GUI_COMPONENTS_DIR}/NaiSysButton.qml
    ${GUI_COMPONENTS_DIR}/NaiSysComboBox.qml
    ${GUI_COMPONENTS_DIR}/NaiSysDialogBox.qml
    ${GUI_COMPONENTS_DIR}/NaiSysDiv.qml
    ${GUI_COMPONENTS_DIR}/NaiSysImageCard.qml
    ${GUI_COMPONENTS_DIR}/NaiSysInputField.qml
    ${GUI_COMPONENTS_DIR}/NaiSysInputForm.qml
    ${GUI_COMPONENTS_DIR}/NaiSysLabel.qml
    ${GUI_COMPONENTS_DIR}/NaiSysListView.qml
    ${GUI_COMPONENTS_DIR}/NaiSysListWidget.qml
    ${GUI_COMPONENTS_DIR}/NaiSysLoadingPopup.qml
    ${GUI_COMPONENTS_DIR}/NaiSysNavigationPane.qml
    ${GUI_COMPONENTS_DIR}/NaiSysProfileHeader.qml
    ${GUI_COMPONENTS_DIR}/NaiSysSlideShow.qml
    ${GUI_COMPONENTS_DIR}/NaiSysTabWidget.qml
    ${GUI_COMPONENTS_DIR}/NaiSysTabButton.qml
    ${GUI_COMPONENTS_DIR}/NaiSysTable.qml
    ${GUI_COMPONENTS_DIR}/NaiSysTableWidget.qml
    ${GUI_COMPONENTS_DIR}/NaiSysTextArea.qml
    ${GUI_COMPONENTS_DIR}/NaiSysText.qml
    ${GUI_COMPONENTS_DIR}/NaiSysTronCard.qml
    ${GUI_COMPONENTS_DIR}/NaiSysTronWidget.qml
    ${GUI_COMPONENTS_DIR}/NaiSysWindow.qml
)

set( LAYOUT_FILES
    ${GUI_LAYOUTS_DIR}/NaiSysDashLayout.qml
    ${GUI_LAYOUTS_DIR}/NaiSysFormLayout.qml
    ${GUI_LAYOUTS_DIR}/NaiSysGridStackLayout.qml
    ${GUI_LAYOUTS_DIR}/NaiSysNavigationLayout.qml
    ${GUI_LAYOUTS_DIR}/NaiSysStackLayout.qml
)

set( PLUGIN_FILES
    ${GUI_PLUGINS_DIR}/naisysformelement.h
    ${GUI_PLUGINS_DIR}/naisysformelement.cpp
    ${GUI_PLUGINS_DIR}/naisysformmodel.h
    ${GUI_PLUGINS_DIR}/naisysformmodel.cpp
    ${GUI_PLUGINS_DIR}/naisysmenu.h
    ${GUI_PLUGINS_DIR}/naisysmenu.cpp
    ${GUI_PLUGINS_DIR}/naisysmenubutton.h
    ${GUI_PLUGINS_DIR}/naisysmenubutton.cpp
    ${GUI_PLUGINS_DIR}/naisysmenuitem.h
    ${GUI_PLUGINS_DIR}/naisysmenuitem.cpp
    ${GUI_PLUGINS_DIR}/naisysmenusection.h
    ${GUI_PLUGINS_DIR}/naisysmenusection.cpp
    ${GUI_PLUGINS_DIR}/naisysnotificationcontroller.h
    ${GUI_PLUGINS_DIR}/naisysnotificationcontroller.cpp
    ${GUI_PLUGINS_DIR}/naisyssubmenu.h
    ${GUI_PLUGINS_DIR}/naisyssubmenu.cpp
    ${GUI_PLUGINS_DIR}/naisysquickwindowexstension.h
    ${GUI_PLUGINS_DIR}/naisysquickwindowexstension.cpp
    ${GUI_PLUGINS_DIR}/naisystabelement.h
    ${GUI_PLUGINS_DIR}/naisystabelement.cpp
)

set( ICON_FILES
    ${GUI_ICONS_DIR}/info_icon.png
    ${GUI_ICONS_DIR}/warning_icon.png
)

set( EXPORT_NAME "libgui")

qt6_add_library( naisysgui STATIC )
qt6_add_qml_module( naisysgui
    URI ${EXPORT_NAME}
    VERSION 1.0
    QML_FILES ${COMPONENT_FILES} ${LAYOUT_FILES}
    SOURCES ${PLUGIN_FILES}
    RESOURCES ${ICON_FILES}
    RESOURCE_PREFIX dev.naisys.net
    IMPORT_PATH ${CMAKE_BINARY_DIR}
)

target_include_directories( naisysgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SOURCE_DIR}
    ${GUI_PLUGINS_DIR}
)

set_target_properties( naisysgui PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.naisys.net
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries( naisysgui
    PRIVATE Qt6::Core
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Widgets
)

install( TARGETS naisysgui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
