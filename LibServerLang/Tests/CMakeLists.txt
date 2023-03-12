cmake_minimum_required(VERSION 3.5)

project(GeneralTests LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test Core Sql Network)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( SERVERLANG_TEST_SCRIPTS
    test1.nsl
    test2.nsl
    test3.nsl
    test4.nsl
    test5.nsl
    test6.nsl
    test7.nsl
    test8.nsl
    test9.nsl
    test10.nsl
    test11.nsl
    test12.nsl
    test13.nsl
    test14.nsl
    test15.nsl
    test15.defs.nsl
    test16.nsl
)

add_executable( GeneralTests
    tst_generaltests.cpp
    ${SERVERLANG_TEST_SCRIPTS}
)
add_test(NAME GeneralTests COMMAND GeneralTests)

target_link_libraries(GeneralTests
    PRIVATE Qt${QT_VERSION_MAJOR}::Test
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
    PRIVATE Qt${QT_VERSION_MAJOR}::Sql
    PRIVATE Qt${QT_VERSION_MAJOR}::Network
    
    naisyssql
    naisysconsole
    naisysserverlang
)

