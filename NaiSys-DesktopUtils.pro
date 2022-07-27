QT -= gui
QT += core sql printsupport

TEMPLATE = lib
DEFINES += NAISYSDESKTOPUTILS_LIBRARY

CONFIG += staticlib
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    consolelogger.cpp \
    databasehandler.cpp \
    naisysdesktoputil.cpp \
    naisysdocumenthandler.cpp \
    naisysjsonobject.cpp \
    naisysprint.cpp \
    naisysxlsx.cpp \
    systemconfig.cpp

HEADERS += \
    consolelogger.h \
    databasehandler.h \
    naisysdesktoputil.h \
    naisysdocumenthandler.h \
    naisysjsonobject.h \
    naisysprint.h \
    naisysxlsx.h \
    systemconfig.h

INCLUDEPATH += QSimpleXlsxWriter/simplexlsx-code

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
