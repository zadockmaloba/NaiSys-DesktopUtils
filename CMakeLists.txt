cmake_minimum_required(VERSION 3.16)

project(NaiSys-HttpServer-Lib VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Core Network Sql PrintSupport Gui REQUIRED)

qt_add_library( NaiSys-DesktopUtils )

target_include_directories( NaiSys-DesktopUtils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/QSimpleXlsxWriter/simplexlsx-code/
)

target_sources( NaiSys-DesktopUtils
PUBLIC
    consolelogger.cpp
    naisysdesktoputil.cpp
    naisysxlsx.cpp
    databasehandler.cpp
    naisysdocumenthandler.cpp
    qmlfileio.cpp
    databasepool.cpp
    naisysjsonobject.cpp
    streamio.cpp
    naisyscompression.cpp
    naisysprint.cpp
    systemconfig.cpp
)

set_target_properties( NaiSys-DesktopUtils PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.naisys.net
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries( NaiSys-DesktopUtils
    PRIVATE Qt6::Core
    PRIVATE Qt6::Network
    PRIVATE Qt6::Sql
    PRIVATE Qt6::PrintSupport
    PRIVATE Qt6::Gui
)

install( TARGETS NaiSys-HttpServer-Lib
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
