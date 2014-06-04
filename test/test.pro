TEMPLATE = app
TARGET = test
INCLUDEPATH += . /usr/include/QDrive
CONFIG += c++11
QT += dbus quick
LIBS += -lqdrive
MOC_DIR = ../tmp
OBJECTS_DIR = ../tmp

SOURCES += test.cpp
