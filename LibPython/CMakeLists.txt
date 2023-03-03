cmake_minimum_required(VERSION 3.16)

project(NaiSys-Python VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(PYTHON_ROOT_DIR ${ROOT_DIR}/thirdparty/cpython)
set(PYTHON_INCLUDE_DIR ${PYTHON_ROOT_DIR}/Include)

find_package(Qt6 6.2 COMPONENTS Core Sql REQUIRED)

qt_add_library( naisyspython STATIC )

target_include_directories( naisyspython PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SOURCE_DIR}
    ${PYTHON_ROOT_DIR}
    ${PYTHON_INCLUDE_DIR}
)

set(PROJECT_HEADERS
    ${SOURCE_DIR}/libpython.h
)
set(PROJECT_SOURCES
    ${SOURCE_DIR}/libpython.cpp
)

target_sources( naisyspython
    PRIVATE ${PROJECT_HEADERS}
    PRIVATE ${PROJECT_SOURCES}
)

set_target_properties( naisyspython PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.naisys.net
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries( naisyspython
    PRIVATE Qt6::Core
    PRIVATE Qt6::Sql
    naisysconsole
    naisyssql
)

install( TARGETS naisyspython
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_custom_command(OUTPUT ${ROOT_DIR}/buildx64/
                   COMMAND make -j2
                   WORKING_DIRECTORY ${ROOT_DIR}/thirdparty/cpython
)
