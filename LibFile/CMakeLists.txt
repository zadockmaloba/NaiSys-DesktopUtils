cmake_minimum_required(VERSION 3.16)

project(NaiSys-File VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)

find_package(Qt6 6.2 COMPONENTS Core REQUIRED)

qt_add_library( naisysfile STATIC )

target_include_directories( naisysfile PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SOURCE_DIR}
)

set(PROJECT_HEADERS
    ${SOURCE_DIR}/naisysdocumenthandler.h
    ${SOURCE_DIR}/qmlfileio.h
)
set(PROJECT_SOURCES
    ${SOURCE_DIR}/naisysdocumenthandler.cpp
    ${SOURCE_DIR}/qmlfileio.cpp
)

target_sources( naisysfile
PRIVATE
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
)

set_target_properties( naisysfile PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.naisys.net
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries( naisysfile
    PRIVATE Qt6::Core
    naisyssettings
    naisysconsole
)

install( TARGETS naisysfile
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
