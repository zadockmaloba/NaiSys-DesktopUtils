cmake_minimum_required(VERSION 3.16)

project(NaiSys-Python VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(PYTHON_ROOT_DIR ${ROOT_DIR}/thirdparty/Lib/cpython)
set(PYTHON_INCLUDE_DIR ${PYTHON_ROOT_DIR}/Include)
set(PYTHON_VERSION "3.10")

if (APPLE)
    set(PYTHON_LINK_LIB ${PYTHON_ROOT_DIR}/OSX/libpython${PYTHON_VERSION}.a)
    set(PYTHON_RUNTIME_EXE ${PYTHON_ROOT_DIR}/OSX/python.exe)
    set(PYTHON_PLATFORM_PATH ${PYTHON_ROOT_DIR}/OSX/)
elseif (WIN32)
    set(PYTHON_LINK_LIB ${PYTHON_ROOT_DIR}/Win32/libpython${PYTHON_VERSION}.a)
    set(PYTHON_RUNTIME_EXE ${PYTHON_ROOT_DIR}/Win32/python.exe)
    set(PYTHON_PLATFORM_PATH ${PYTHON_ROOT_DIR}/Win32/)
elseif (UNIX)
    set(PYTHON_LINK_LIB ${PYTHON_ROOT_DIR}/Linux/libpython${PYTHON_VERSION}.a)
    set(PYTHON_RUNTIME_EXE ${PYTHON_ROOT_DIR}/Linux/python)
    set(PYTHON_PLATFORM_PATH ${PYTHON_ROOT_DIR}/Linux/)
endif()

add_library( naisyspython STATIC )

target_include_directories( naisyspython PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SOURCE_DIR}
    ${PYTHON_ROOT_DIR}
    ${PYTHON_INCLUDE_DIR}
    ${PYTHON_PLATFORM_PATH}
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

configure_file(
    ${PYTHON_RUNTIME_EXE}
    ${CMAKE_CURRENT_BINARY_DIR}/python
)

add_custom_command(
    TARGET naisyspython POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PYTHON_PLATFORM_PATH}/pythonlib ${CMAKE_CURRENT_BINARY_DIR}/pythonlib
)

target_link_libraries( naisyspython
    ${PYTHON_LINK_LIB}
)

install(
    PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/python
    DESTINATION .
)

install( TARGETS naisyspython
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
