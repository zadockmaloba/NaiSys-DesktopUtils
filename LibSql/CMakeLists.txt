cmake_minimum_required(VERSION 3.16)

project(NaiSys-Sql VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(POSTGRES_ROOT_DIR ${ROOT_DIR}/thirdparty/Lib/postgres)
set(POSTGRES_INCLUDE_DIR ${POSTGRES_ROOT_DIR}/Include)

find_package(Qt6 6.2 COMPONENTS Core Network Sql REQUIRED)

qt_add_library( naisyssql STATIC )

if (APPLE)
    set(POSTGRES_LINK_LIB ${POSTGRES_ROOT_DIR}/OSX/libpq.a)
    set(POSTGRES_DYNAMIC_LINK_LIB ${POSTGRES_ROOT_DIR}/OSX/libpq.5.dylib)
    #set(POSTGRES_RUNTIME_EXE ${POSTGRES_ROOT_DIR}/OSX/python.exe)
    set(POSTGRES_PLATFORM_PATH ${POSTGRES_ROOT_DIR}/OSX/)
    configure_file(
        ${POSTGRES_DYNAMIC_LINK_LIB}
        ${CMAKE_BINARY_DIR}/libpq.dylib
    )
elseif (WIN32)
    set(POSTGRES_LINK_LIB ${POSTGRES_ROOT_DIR}/Win32/libpq.a)
    set(POSTGRES_DYNAMIC_LINK_LIB ${POSTGRES_ROOT_DIR}/Win32/libpq.dll)
    set(POSTGRES_PLATFORM_PATH ${POSTGRES_ROOT_DIR}/Win32/)
    configure_file(
        ${POSTGRES_DYNAMIC_LINK_LIB}
        ${CMAKE_BINARY_DIR}/libpq.dll
    )
elseif (UNIX)
    set(POSTGRES_LINK_LIB ${POSTGRES_ROOT_DIR}/Linux/libpq.a)
    set(POSTGRES_DYNAMIC_LINK_LIB ${POSTGRES_ROOT_DIR}/Linux/libpq.so.5.16)
    set(POSTGRES_PLATFORM_PATH ${POSTGRES_ROOT_DIR}/Linux/)
    configure_file(
        ${POSTGRES_DYNAMIC_LINK_LIB}
        ${CMAKE_BINARY_DIR}/libpq.so
    )
endif()

target_include_directories( naisyssql PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SOURCE_DIR}
    ${POSTGRES_ROOT_DIR}
    ${POSTGRES_INCLUDE_DIR}
)

set(PROJECT_HEADERS
    ${SOURCE_DIR}/databasehandler.h
    ${SOURCE_DIR}/databasepool.h
)
set(PROJECT_SOURCES
    ${SOURCE_DIR}/databasehandler.cpp
    ${SOURCE_DIR}/databasepool.cpp
)

target_sources( naisyssql
PRIVATE
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
)

set_target_properties( naisyssql PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.naisys.net
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries( naisyssql
    PRIVATE Qt6::Core
    PRIVATE Qt6::Network
    PRIVATE Qt6::Sql
    naisysconsole
    naisyssettings
    naisysjson
    ${POSTGRES_LINK_LIB}
)

install( TARGETS naisyssql
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
