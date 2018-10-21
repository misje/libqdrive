/**
 * \author Andreas Misje
 * \date 2017
 * \copyright MIT
 */

#pragma once
#include "DBusObject.h"

namespace QDrive
{
	/** \brief Block device object based on UDisks2.Block interface
	 *
	 * Check the <a href="http://udisks.freedesktop.org/docs/latest/">UDisks2
	 * documentation</a> for information about properties
	 */
	class BlockDevice : public DBusObject
	{
		Q_OBJECT
		Q_PROPERTY(QString device READ device CONSTANT)
		Q_PROPERTY(QString preferredDevice READ preferredDevice CONSTANT)
		Q_PROPERTY(QStringList symlinks READ symlinks CONSTANT)
		Q_PROPERTY(int deviceNumber READ deviceNumber CONSTANT)
		Q_PROPERTY(QString id READ id CONSTANT)
		Q_PROPERTY(qulonglong size READ size CONSTANT)
		Q_PROPERTY(bool readOnly READ isReadOnly CONSTANT)
		Q_PROPERTY(QDBusObjectPath drive READ drive CONSTANT)
		Q_PROPERTY(QObject *driveObject READ driveObject CONSTANT)
		/* TODO: Add RAID object and accessor */
		Q_PROPERTY(QString usage READ usage CONSTANT)
		Q_PROPERTY(QString type READ type CONSTANT)
		Q_PROPERTY(QString label READ label CONSTANT)
		Q_PROPERTY(QString uuid READ uuid CONSTANT)
		Q_PROPERTY(QDBusObjectPath cryptoDevicePath READ cryptoDevicePath CONSTANT)
		Q_PROPERTY(QObject *cryptoDeviceObject READ cryptoDeviceObject CONSTANT)
		Q_PROPERTY(bool system READ isSystem CONSTANT)
		Q_PROPERTY(QString name READ name CONSTANT)

	public:
		BlockDevice(const QDBusObjectPath &path, QObject *parent = nullptr);

		/** \brief Tells whether object is a block device by calling
		 * isBlockDevice() */
		bool isValid() const override;
		/** \brief Check whether object at given path is a block device
		 *
		 * This function calls introspect() and ensures that the object provides
		 * the <a
		 * href="http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Block.html">UDisks2
		 * Blockdevice interface</a>
		 */
		static bool isBlockDevice(const QDBusObjectPath &path, int replyTimeout);
		/** \brief Check the given list of interfaces to see whether it contains
		 * <a
		 * href="http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Block.html"Block
		 * device</a>
		 */
		static bool isBlockDevice(const QList<QString> &interfaces);

		QString device() const;
		QString preferredDevice() const;
		QStringList symlinks() const;
		int deviceNumber() const;
		QString id() const;
		qulonglong size() const;
		bool isReadOnly() const;
		QDBusObjectPath drive() const;
		QObject *driveObject();
		QString usage() const;
		QString type() const;
		QString label() const;
		QString uuid() const;
		QDBusObjectPath cryptoDevicePath() const;
		QObject *cryptoDeviceObject();
		bool isSystem() const;
		QString name() const;
		bool hasFileSystem() const;
		QDBusObjectPath fileSystem() const;
	};
}

QDebug operator <<(QDebug d, const QDrive::BlockDevice &blockDevice);
