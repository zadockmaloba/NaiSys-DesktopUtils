cmake_minimum_required(VERSION 3.16)

project(NaiSys-Core VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++17")
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)

find_package(Qt6 6.2 COMPONENTS Core Sql REQUIRED)

#qt_add_library( naisyscore STATIC )

#target_include_directories( naisyscore PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}
#    ${SOURCE_DIR}
#)

set(PROJECT_HEADERS
    ${SOURCE_DIR}/naisysindexedmap.h 
)

#target_sources( naisyscore
#    PRIVATE ${PROJECT_HEADERS}
#    PRIVATE ${PROJECT_SOURCES}
#)

#set_target_properties( naisyscore PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER dev.naisys.net
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE FALSE
#)

#target_link_libraries( naisyscore
#    PRIVATE Qt6::Core
#)

#install( TARGETS naisyscore
#    BUNDLE DESTINATION .
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#)
