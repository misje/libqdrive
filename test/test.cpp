/**
 * \author Andreas Misje
 * \date 2014
 * \copyright MIT
 */

#include <QGuiApplication>
#include <QDrive.h>
#include <Monitor.h>
#include <Drive.h>
#include <Partition.h>
#include <PartitionListModel.h>
#include <QQuickView>
#include <QtQml>
#include <QDebug>

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	{
		/* List all drives on the system on the command line: */
	 	QList<QDBusObjectPath> drivePaths = QDrive::drives(100);
		foreach (const QDBusObjectPath &path, drivePaths)
			qDebug() << QDrive::Drive(path);
	}
	{
		/* List all partitions on the system on the command line: */
	 	QList<QDBusObjectPath> partitionPaths = QDrive::partitions(100);
		foreach (const QDBusObjectPath &path, partitionPaths)
			qDebug() << QDrive::Partition(path);
	}

	QDrive::Monitor m;
	QObject::connect(&m, &QDrive::Monitor::driveAdded, [](const QDBusObjectPath 
				&path) {
			qDebug() << "Drive added:";
			qDebug() << QDrive::Drive(path);
			} );
	QObject::connect(&m, &QDrive::Monitor::partitionAdded, [](const QDBusObjectPath 
				&path) {
			qDebug() << "Partition added:";
			qDebug() << QDrive::Partition(path);
			} );
	QObject::connect(&m, &QDrive::Monitor::driveRemoved, [](const QDBusObjectPath 
				&path) {
			qDebug() << "Drive removed:" << path.path();
			} );
	QObject::connect(&m, &QDrive::Monitor::partitionRemoved, [](const QDBusObjectPath 
				&path) {
			qDebug() << "Partition removed:" << path.path();
			} );

	qmlRegisterType<QDrive::PartitionListModel>("QDrive", 1, 0, "PartitionListModel");

	QQuickView viewer;
	viewer.setResizeMode(QQuickView::SizeRootObjectToView);
	viewer.setSource(QUrl::fromLocalFile("test.qml"));
	viewer.show();
	
	return app.exec();
}
