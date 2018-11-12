/**
 * \author Andreas Misje
 * \date 2017
 * \copyright MIT
 */

#include "FileSystem.h"
#include "QDrive.h"
#include "AvailableSpace.h"
using namespace QDrive;
#include <QDBusConnection>
#include <QDBusArgument>
#include <QDBusError>
#include <QDBusMessage>
#include <QDBusReply>

FileSystem::FileSystem(const QDBusObjectPath &path, QObject *parent)
	: DBusObject(path, parent)
{
	QDBusConnection sys = QDBusConnection::systemBus();
	bool connectionOK = sys.connect( UDisks2::service(), path.path(), 
			Interface::Properties(), "PropertiesChanged", this, SLOT(
				inspectFileSysPropertyChanges(const QString &, const QVariantMap &, 
					const QStringList &)));

	if (!connectionOK)
		throw DBusException("Could not connect PropertiesChanged signal");
}

bool FileSystem::isValid() const
{
	try
	{
		return isFileSystem(path(), replyTimeout());
	}
	catch (const DBusException &exception)
	{
		return false;
	}
}

bool FileSystem::isFileSystem(const QDBusObjectPath &path, int replyTimeout)
{
	return QDrive::hasInterface(path, Interface::UDisks2("Filesystem"), replyTimeout);
}

bool FileSystem::isFileSystem(const QList<QString> &interfaces)
{
	return interfaces.contains(Interface::UDisks2("Filesystem"));
}

bool FileSystem::isMounted() const
{
	return !mountPoints().isEmpty();
}

QStringList FileSystem::mountPoints() const
{
	const QDBusArgument rawList = dbusProperty(Interface::UDisks2("Filesystem"), 
			"MountPoints").value<QDBusArgument>();

	return aayToStringList(rawList);
}

quint64 FileSystem::availableSpace() const
{
	if (!isMounted())
		return 0;

	return QDrive::availableSpace(mountPoints().at(0));
}

quint64 FileSystem::totalSpace() const
{
	if (!isMounted())
		return 0;

	return QDrive::totalSpace(mountPoints().at(0));
}

QDBusObjectPath FileSystem::blockDevice() const
{
	return path();
}

void FileSystem::mount() const
{
	QDBusConnection sys = QDBusConnection::systemBus();
	QDBusMessage mount = QDBusMessage::createMethodCall(UDisks2::service(), 
			path().path(), Interface::UDisks2("Filesystem"), "Mount");

	QVariantList arguments;
	QVariantMap options;
	options["auth.no_user_interaction"] = true;
	arguments << options;

	mount.setArguments(arguments);

	QDBusReply<QString> reply = sys.call(mount, QDBus::Block, replyTimeout());
	if (!reply.isValid())
		throw DBusException(reply.error().message().toStdString());
}

void FileSystem::unmount(bool force) const
{
	QDBusConnection sys = QDBusConnection::systemBus();
	QDBusMessage unmount = QDBusMessage::createMethodCall(UDisks2::service(), 
			path().path(), Interface::UDisks2("Filesystem"), "Unmount");

	QVariantList arguments;
	QVariantMap options;
	if (force)
		options["force"] = true;

	arguments << options;

	unmount.setArguments(arguments);

	/* TODO: This can return an error. Please catch it … */
	sys.call(unmount, QDBus::NoBlock);
}

void FileSystem::inspectFileSysPropertyChanges(const QString &interface, const 
		QVariantMap &changedProperties, const QStringList &invalidatedProperties)
{
	Q_UNUSED(interface);

	if (invalidatedProperties.contains("MountPoints"))
	{
		emit mountPointsChanged({});
		return;
	}

	if (changedProperties.contains("MountPoints"))
		emit mountPointsChanged(aayToStringList(changedProperties.value(
						"MountPoints").value<QDBusArgument>()));
}


QDebug operator <<(QDebug d, const QDrive::FileSystem &fileSystem)
{
	d.nospace() << "FileSystem " << fileSystem.path().path() << ":\n";

	bool valid = fileSystem.isValid();
	d.nospace() << "  valid:\t\t" << valid;
	if (valid)
	{
		d.nospace() << "\n  mounted:\t\t" << fileSystem.isMounted() << '\n';
		d.nospace() << "  mount points:\t\t" << fileSystem.mountPoints();
	}

	return d.nospace();
}
