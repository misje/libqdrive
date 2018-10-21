TEMPLATE = lib
CONFIG *= c++11 warn_on staticlib
QMAKE_CXXFLAGS *= -Wall -Wextra -pedantic
QT *= dbus
QT -= gui
TARGET = qdrive
DESTDIR = .
MOC_DIR = tmp
OBJECTS_DIR = tmp
INCLUDEPATH *= include

HEADERS += \
	include/AvailableSpace.h \
	include/BlockDevice.h \
	include/DBusObject.h \
	include/Drive.h \
	include/FileSystem.h \
	include/Monitor.h \
	include/Partition.h \
	include/QDrive.h \
	include/Version.h

SOURCES += \
	src/AvailableSpace.cpp \
	src/BlockDevice.cpp \
	src/DBusObject.cpp \
	src/Drive.cpp \
	src/FileSystem.cpp \
	src/Monitor.cpp \
	src/Partition.cpp \
	src/QDrive.cpp

sharedlib {
	CONFIG -= staticlib
}

libfiles.files = $${DESTDIR}/lib$${TARGET}.a
libfiles.path = /usr/lib/

headerfiles.files = $$HEADERS
headerfiles.path = $${DESTDIR}/usr/include/QDrive/

INSTALLS += libfiles headerfiles
