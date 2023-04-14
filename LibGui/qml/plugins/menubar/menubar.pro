TEMPLATE = lib
CONFIG += qt plugin qmltypes
QT += qml \
      quick \
      core

QML_IMPORT_NAME = NaiSysMenuBar
QML_IMPORT_MAJOR_VERSION = 1

DESTDIR = ../../components
TARGET  = naisysqmlmenubar

SOURCES += \
    naisysmenubar.cpp \
    plugin.cpp

HEADERS += \
    naisysmenubar.h
