TEMPLATE = app
TARGET = test
INCLUDEPATH += . ../src
CONFIG += c++11
QT += dbus
QT -= gui
LIBS += -L.. -lqdrive
MOC_DIR = ../tmp
OBJECTS_DIR = ../tmp

SOURCES += test.cpp
