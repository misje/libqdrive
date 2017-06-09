/**
 * \author Andreas Misje
 * \date 2014
 * \copyright MIT
 */

#include "QDrive.h"
#include "Partition.h"
#include "Drive.h"
#include "FileSystem.h"
using namespace QDrive;

Partition::Partition(const QDBusObjectPath &path, QObject *parent)
	: DBusObject(path, parent)
{
}

bool Partition::isValid() const
{
	try
	{
		return isPartition(path(), replyTimeout());
	}
	catch (const DBusException &exception)
	{
		return false;
	}
}

bool Partition::isPartition(const QDBusObjectPath &path, int replyTimeout)
{
	return QDrive::hasInterface(path, Interface::UDisks2("Partition"), replyTimeout);
}

bool Partition::isPartition(const QList<QString> &interfaces)
{
	return interfaces.contains(Interface::UDisks2("Partition"));
}

int Partition::partitionNumber() const
{
	return dbusProperty(Interface::UDisks2("Partition"), "Number").toInt();
}

qulonglong Partition::offset() const
{
	return dbusProperty(Interface::UDisks2("Partition"), "Offset").toULongLong();
}

QString Partition::type() const
{
	return dbusProperty(Interface::UDisks2("Partition"), "Type").toString();
}

QDBusObjectPath Partition::blockDevice() const
{
	return path();
}

bool Partition::hasFileSystem() const
{
	return FileSystem::isFileSystem(path(), replyTimeout());
}

QDBusObjectPath Partition::fileSystem() const
{
	if (hasFileSystem())
		return path();

	return {};
}


QDebug operator <<(QDebug d, const QDrive::Partition &partition)
{
	d.nospace() << "Partition " << partition.path().path() << ":\n";

	bool valid = partition.isValid();
	d.nospace() << "  valid:\t\t" << valid;
	if (valid)
	{
		d.nospace() << "\n  partition number:\t" << partition.partitionNumber() << '\n';
		d.nospace() << "  offset:\t\t" << partition.offset() << '\n';
		d.nospace() << "  type:\t\t\t" << partition.type() << '\n';
	}

	return d.nospace();
}
