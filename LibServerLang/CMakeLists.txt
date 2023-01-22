cmake_minimum_required(VERSION 3.16)

project(NaiSys-ServerLang VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)

find_package(Qt6 6.2 COMPONENTS Core Sql REQUIRED)

qt_add_library( naisysserverlang STATIC )

target_include_directories( naisysserverlang PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SOURCE_DIR}
)

add_subdirectory(Tests)

set(PROJECT_HEADERS
    ${SOURCE_DIR}/serverlangfunctions.h
    ${SOURCE_DIR}/serverlanglexer.h
    ${SOURCE_DIR}/serverlangnode.h
    ${SOURCE_DIR}/serverlangparser.h
    ${SOURCE_DIR}/serverlangruntime.h
    ${SOURCE_DIR}/serverlangsyntaxtree.h
    ${SOURCE_DIR}/serverlangtypes.h
)
set(PROJECT_SOURCES
    ${SOURCE_DIR}/serverlangnode.cpp
    ${SOURCE_DIR}/serverlangparser.cpp
    ${SOURCE_DIR}/serverlangruntime.cpp
    ${SOURCE_DIR}/serverlangsyntaxtree.cpp
)

target_sources( naisysserverlang
    PRIVATE ${PROJECT_HEADERS}
    PRIVATE ${PROJECT_SOURCES}
)

set_target_properties( naisysserverlang PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.naisys.net
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries( naisysserverlang
    PRIVATE Qt6::Core
    PRIVATE Qt6::Sql
    naisysconsole
    naisyssql
)

install( TARGETS naisysserverlang
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
