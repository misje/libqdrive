/**
 * \author Andreas Misje
 * \date 2017
 * \copyright MIT
 */

#include "QDrive.h"
#include "BlockDevice.h"
#include "FileSystem.h"
using namespace QDrive;
#include <QDBusArgument>

BlockDevice::BlockDevice(const QDBusObjectPath &path, QObject *parent)
	: DBusObject(path, parent)
{
}

bool BlockDevice::isValid() const
{
	try
	{
		return isBlockDevice(path(),replyTimeout());
	}
	catch (const DBusException &exception)
	{
		return false;
	}
}

bool BlockDevice::isBlockDevice(const QDBusObjectPath &path, int replyTimeout)
{
	return QDrive::hasInterface(path, Interface::UDisks2("Block"), replyTimeout);
}

bool BlockDevice::isBlockDevice(const QList<QString> &interfaces)
{
	return interfaces.contains(Interface::UDisks2("Block"));
}

QString BlockDevice::device() const
{
	return dbusProperty(Interface::UDisks2("Block"), "Device").toString();
}

QString BlockDevice::preferredDevice() const
{
	return dbusProperty(Interface::UDisks2("Block"), "PreferredDevice").toString();
}

QStringList BlockDevice::symlinks() const
{
	return aayToStringList(dbusProperty(Interface::UDisks2("Block"), "Symlinks")
			.value<QDBusArgument>());
}

int BlockDevice::deviceNumber() const
{
	return dbusProperty(Interface::UDisks2("Block"), "DeviceNumber").toInt();
}

QString BlockDevice::id() const
{
	return dbusProperty(Interface::UDisks2("Block"), "Id").toString();
}

qulonglong BlockDevice::size() const
{
	return dbusProperty(Interface::UDisks2("Block"), "Size").toULongLong();
}

bool BlockDevice::isReadOnly() const
{
	return dbusProperty(Interface::UDisks2("Block"), "ReadOnly").toBool();
}

QDBusObjectPath BlockDevice::drive() const
{
	auto path = dbusProperty(Interface::UDisks2("Block"), "Drive").value<QDBusObjectPath>();
	if (path.path() == "/")
		return {};
	
	return path;
}

QObject *BlockDevice::driveObject() const
{
	return new Drive(drive());
}

QString BlockDevice::usage() const
{
	return dbusProperty(Interface::UDisks2("Block"), "IdUsage").toString();
}

QString BlockDevice::type() const
{
	return dbusProperty(Interface::UDisks2("Block"), "IdType").toString();
}

QString BlockDevice::label() const
{
	return dbusProperty(Interface::UDisks2("Block"), "IdLabel").toString();
}

QString BlockDevice::uuid() const
{
	return dbusProperty(Interface::UDisks2("Block"), "IdUUID").toString();
}

QDBusObjectPath BlockDevice::cryptoDevicePath() const
{
	return dbusProperty(Interface::UDisks2("Block"), "CryptoBackingDevice").value<QDBusObjectPath>();
}

QObject *BlockDevice::cryptoDeviceObject()
{
	auto path = cryptoDevicePath();
	if (!path.path().isEmpty())
		return new BlockDevice(path, this);

	return {};
}

bool BlockDevice::isSystem() const
{
	return dbusProperty(Interface::UDisks2("Block"), "HintSystem").toBool();
}

QString BlockDevice::name() const
{
	return dbusProperty(Interface::UDisks2("Block"), "HintName").toString();
}

bool BlockDevice::hasFileSystem() const
{
	return FileSystem::isFileSystem(path(), replyTimeout());
}

QDBusObjectPath BlockDevice::fileSystem() const
{
	if (hasFileSystem())
		return path();

	return {};
}


QDebug operator <<(QDebug d, const QDrive::BlockDevice &blockDevice)
{
	d.nospace() << "Block device " << blockDevice.path().path() << ":\n";

	bool valid = blockDevice.isValid();
	d.nospace() << "  valid:\t\t" << valid;
	if (valid)
	{
		d.nospace() << "\n  device:\t\t" << blockDevice.device() << '\n';
		d.nospace() << "  ID:\t\t\t" << blockDevice.id() << '\n';
		d.nospace() << "  size:\t\t\t" << blockDevice.size() << '\n';
		d.nospace() << "  read-only:\t\t" << blockDevice.isReadOnly() << '\n';
		d.nospace() << "  drive:\t\t" << blockDevice.drive().path() << '\n';
		d.nospace() << "  label:\t\t" << blockDevice.label() << '\n';
		d.nospace() << "  UUID:\t\t\t" << blockDevice.uuid() << '\n';
		d.nospace() << "  symlinks:\t\t" << blockDevice.symlinks() << '\n';
		d.nospace() << "  has fs:\t\t" << blockDevice.hasFileSystem() << '\n';
	}

	return d.nospace();
}
