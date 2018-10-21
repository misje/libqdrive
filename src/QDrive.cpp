/**
 * \author Andreas Misje
 * \date 2014
 * \copyright MIT
 */

#include "QDrive.h"
#include "DBusObject.h"
#include <QStringBuilder>
#include <QDBusConnection>
#include <QDBusError>
#include <QXmlStreamReader>

static QList<QDBusObjectPath> blockDevices(int replyTimeout, const QString &interfaceFilter);


QString QDrive::UDisks2::service()
{ 
	return "org.freedesktop.UDisks2";
}

QString QDrive::UDisks2::path()
{
	return "/org/freedesktop/UDisks2";
}

QString QDrive::UDisks2::path(const QString &subPath)
{
	return QString(path() % '/' % subPath);
}

QString QDrive::Interface::UDisks2()
{
	return "org.freedesktop.UDisks2";
}

QString QDrive::Interface::UDisks2(const QString &interface)
{
	return QString(UDisks2() % '.' % interface);
}

QString QDrive::Interface::ObjectManager()
{
	return "org.freedesktop.DBus.ObjectManager";
}

QString QDrive::Interface::Introspectable()
{
	return "org.freedesktop.DBus.Introspectable";
}

QString QDrive::Interface::Properties()
{
	return "org.freedesktop.DBus.Properties";
}

bool QDrive::hasInterface(const QDBusObjectPath &path, const QString &interface,
		int replyTimeout)
{
	QXmlStreamReader xml(DBusObject::introspect(path.path(), replyTimeout));
	while (!xml.atEnd())
	{
		xml.readNext();
		if (xml.isStartElement() && xml.name() == "interface" && xml.attributes()
				.value("name") == interface)
			return true;
	}

	return false;
}

QList<QDBusObjectPath> QDrive::drives(int replyTimeout)
{
	QXmlStreamReader xml(DBusObject::introspect(QDrive::UDisks2::path("drives"),
				replyTimeout));

	QList<QDBusObjectPath> drives;
	while (!xml.atEnd())
	{
		xml.readNext();
		if (xml.isStartElement() && xml.name() == "node" && xml.attributes()
				.hasAttribute("name"))
			drives << QDBusObjectPath(QDrive::UDisks2::path() % "/drives/" %
					xml.attributes().value("name"));
	}

	return drives;
}

QList<QDBusObjectPath> QDrive::blockDevices(int replyTimeout)
{
	return ::blockDevices(replyTimeout, {});
}

QList<QDBusObjectPath> QDrive::partitions(int replyTimeout)
{
	return ::blockDevices(replyTimeout, Interface::UDisks2("Partition"));
}

QList<QDBusObjectPath> QDrive::fileSystems(int replyTimeout)
{
	return ::blockDevices(replyTimeout, Interface::UDisks2("Filesystem"));
}

QDebug operator <<(QDebug d, const QDBusObjectPath &path)
{
	d << path.path();

	return d;
}


static QList<QDBusObjectPath> blockDevices(int replyTimeout, const QString &interfaceFilter)
{
	QXmlStreamReader xml(QDrive::DBusObject::introspect(QDrive::UDisks2::path(
					"block_devices"), replyTimeout));

	QList<QDBusObjectPath> devices;
	while (!xml.atEnd())
	{
		xml.readNext();
		if (xml.isStartElement() && xml.name() == "node" && xml.attributes()
				.hasAttribute("name"))
		{
			QDBusObjectPath path(QDrive::UDisks2::path() % "/block_devices/" %
					xml.attributes().value("name"));

			if (interfaceFilter.isEmpty() || QDrive::hasInterface(path, interfaceFilter,
						replyTimeout))
				devices << path;
		}
	}

	return devices;
}
