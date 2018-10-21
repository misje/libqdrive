TEMPLATE = lib
CONFIG += c++11 warn_on staticlib
QT += dbus
TARGET = qdrive
DESTDIR = .
MOC_DIR = tmp
OBJECTS_DIR = tmp

HEADERS += \
	src/AvailableSpace.h \
	src/BlockDevice.h \
	src/DBusObject.h \
	src/Drive.h \
	src/FileSystem.h \
	src/Monitor.h \
	src/Partition.h \
	src/QDrive.h \
	src/Version.h

SOURCES += \
	src/AvailableSpace.cpp \
	src/BlockDevice.cpp \
	src/DBusObject.cpp \
	src/Drive.cpp \
	src/FileSystem.cpp \
	src/Monitor.cpp \
	src/Partition.cpp \
	src/QDrive.cpp

libfiles.files = $${DESTDIR}/lib$${TARGET}.a
libfiles.path = /usr/lib/

headerfiles.files = $$HEADERS
headerfiles.path = /usr/include/QDrive/

INSTALLS += libfiles headerfiles
