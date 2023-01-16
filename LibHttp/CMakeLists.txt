cmake_minimum_required(VERSION 3.16)

project(NaiSys-Http VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)

find_package(Qt6 6.2 COMPONENTS Core REQUIRED)

qt_add_library( naisyshttp )

target_include_directories( naisyshttp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SOURCE_DIR}
)

set(PROJECT_HEADERS
    ${SOURCE_DIR}/connectionthread.h
    ${SOURCE_DIR}/naisysdefs.h
    ${SOURCE_DIR}/naisyshttpparser.h
    ${SOURCE_DIR}/naisyshttprequest.h
    ${SOURCE_DIR}/naisyshttpresponse.h
    ${SOURCE_DIR}/naisyshttpserver.h
    ${SOURCE_DIR}/naisysmethodhandler.h
    ${SOURCE_DIR}/servercalls.h
)
set(PROJECT_SOURCES
    ${SOURCE_DIR}/connectionthread.cpp
    ${SOURCE_DIR}/naisyshttpparser.cpp
    ${SOURCE_DIR}/naisyshttprequest.cpp
    ${SOURCE_DIR}/naisyshttpresponse.cpp
    ${SOURCE_DIR}/naisyshttpserver.cpp
    ${SOURCE_DIR}/naisysmethodhandler.cpp
    ${SOURCE_DIR}/serverobject.cpp
)

target_sources( naisyshttp
    PRIVATE ${PROJECT_HEADERS}
    PRIVATE ${PROJECT_SOURCES}
)

set_target_properties( naisyshttp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.naisys.net
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries( naisyshttp
    PRIVATE Qt6::Core
)

install( TARGETS naisyshttp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
