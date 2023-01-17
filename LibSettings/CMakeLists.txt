cmake_minimum_required(VERSION 3.16)

project(NaiSys-Settings VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)

find_package(Qt6 6.2 COMPONENTS Core Network Sql PrintSupport Gui REQUIRED)

qt_add_library( naisyssettings STATIC )

target_include_directories( naisyssettings PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SOURCE_DIR}
)

set(PROJECT_HEADERS
    ${SOURCE_DIR}/systemconfig.h
)
set(PROJECT_SOURCES
    ${SOURCE_DIR}/systemconfig.cpp
)

target_sources( naisyssettings
PRIVATE
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
)

set_target_properties( naisyssettings PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.naisys.net
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries( naisyssettings
    PRIVATE Qt6::Core
)

install( TARGETS naisyssettings
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
