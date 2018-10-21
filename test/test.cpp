/**
 * \author Andreas Misje
 * \date 2014
 * \copyright MIT
 */

#include <QCoreApplication>
#include <QDrive.h>
#include <Monitor.h>
#include <Drive.h>
#include <Partition.h>
#include "BlockDevice.h"
#include "FileSystem.h"
#include <QDebug>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	qDebug() << "Drives:";
	for (const auto &path : QDrive::drives(100))
		qDebug() << QDrive::Drive(path);

	qDebug() << "Block devices:";
	for (const auto &path : QDrive::blockDevices(100))
		qDebug() << QDrive::BlockDevice(path);

	qDebug() << "Partitions:";
	for (const auto &path : QDrive::partitions(100))
		qDebug() << QDrive::Partition(path);

	qDebug() << "File systems:";
	for (const auto &path : QDrive::fileSystems(100))
		qDebug() << QDrive::FileSystem(path);

	QDrive::Monitor m;
	QObject::connect(&m, &QDrive::Monitor::driveAdded, [](const QDBusObjectPath 
				&path) {
		qDebug() << "Drive added:";
		qDebug() << QDrive::Drive(path);
	});
	QObject::connect(&m, &QDrive::Monitor::partitionAdded, [](const QDBusObjectPath 
				&path) {
		qDebug() << "Partition added:";
		qDebug() << QDrive::Partition(path);
	});
	QObject::connect(&m, &QDrive::Monitor::blockDeviceAdded, [](const QDBusObjectPath
				&path) {
		qDebug() << "Block device added:";
		qDebug() << QDrive::BlockDevice(path);
	});
	QObject::connect(&m, &QDrive::Monitor::fileSystemAdded, [](const QDBusObjectPath
				&path) {
		qDebug() << "File system added:";
		qDebug() << QDrive::FileSystem(path);
	});
	QObject::connect(&m, &QDrive::Monitor::driveRemoved, [](const QDBusObjectPath 
				&path) { qDebug() << "Drive removed:" << path.path(); });
	QObject::connect(&m, &QDrive::Monitor::partitionRemoved, [](const QDBusObjectPath 
				&path) { qDebug() << "Partition removed:" << path.path(); });
	QObject::connect(&m, &QDrive::Monitor::blockDeviceRemoved, [](const QDBusObjectPath 
				&path) { qDebug() << "Block device removed:" << path.path(); });
	QObject::connect(&m, &QDrive::Monitor::fileSystemRemoved, [](const QDBusObjectPath 
				&path) { qDebug() << "File system removed:" << path.path(); });
	
	return app.exec();
}
