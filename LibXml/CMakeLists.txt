cmake_minimum_required(VERSION 3.16)

project(NaiSys-Xml VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)

find_package(Qt6 6.2 COMPONENTS Core Network Sql REQUIRED)

qt_add_library( naisysxml )

target_include_directories( naisysxml PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SOURCE_DIR}
)

set(PROJECT_HEADERS

)
set(PROJECT_SOURCES

)

target_sources( naisysxml
PRIVATE
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
)

set_target_properties( naisysxml PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.naisys.net
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries( naisysxml
    PRIVATE Qt6::Core
)

install( TARGETS naisysxml
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
