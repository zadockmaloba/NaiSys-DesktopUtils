cmake_minimum_required(VERSION 3.16)

project(NaiSys-ServerLang VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++17 -stdlib=libc++")
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)

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
    ${SOURCE_DIR}/serverlangcore.h
)
set(PROJECT_SOURCES
    ${SOURCE_DIR}/serverlangnode.cpp
    ${SOURCE_DIR}/serverlangparser.cpp
    ${SOURCE_DIR}/serverlangruntime.cpp
    ${SOURCE_DIR}/serverlangsyntaxtree.cpp
    ${SOURCE_DIR}/serverlangcore.cpp
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
    #naisyspython
    
)

install( TARGETS naisysserverlang
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
