TEMPLATE = lib
CONFIG += staticlib
QT += dbus
TARGET = qdrive
DESTDIR = .
MOC_DIR = tmp
OBJECTS_DIR = tmp

HEADERS += \
	src/Version.h \
	src/QDrive.h \
	src/DBusObject.h \
	src/Drive.h \
	src/Partition.h \
	src/Monitor.h \
	src/AvailableSpace.h \
	src/PartitionListModel.h

SOURCES += \
	src/Version.cpp \
	src/QDrive.cpp \
	src/DBusObject.cpp \
	src/Drive.cpp \
	src/Partition.cpp \
	src/Monitor.cpp \
	src/AvailableSpace.cpp \
	src/PartitionListModel.cpp

libfiles.files = $${DESTDIR}/lib$${TARGET}.a
libfiles.path = /usr/lib/

headerfiles.files = $$HEADERS
headerfiles.path = /usr/include/QDrive/

INSTALLS += libfiles headerfiles
