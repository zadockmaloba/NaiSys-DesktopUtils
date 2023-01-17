cmake_minimum_required(VERSION 3.16)

project(NaiSys-Print VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)

find_package(Qt6 6.2 COMPONENTS Core Network Sql PrintSupport Gui REQUIRED)

qt_add_library( naisysprint STATIC )

target_include_directories( naisysprint PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SOURCE_DIR}
)

set(PROJECT_HEADERS
    ${SOURCE_DIR}/naisysprint.h
    ${SOURCE_DIR}/naisysdocumenthandler.h
)
set(PROJECT_SOURCES
    ${SOURCE_DIR}/naisysprint.cpp
    ${SOURCE_DIR}/naisysdocumenthandler.cpp
)

target_sources( naisysprint
PRIVATE
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
)

set_target_properties( naisysprint PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.naisys.net
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries( naisysprint
    PRIVATE Qt6::Core
    PRIVATE Qt6::Sql
    PRIVATE Qt6::Network
    PRIVATE Qt6::PrintSupport
    PRIVATE Qt6::Gui
    naisyssettings
    naisysjson
)

install( TARGETS naisysprint
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
