/**
 * \author Andreas Misje
 * \date 2017
 * \copyright MIT
 */

#pragma once

#include "DBusObject.h"
#include <QDebug>

namespace QDrive
{
	class FileSystem : public DBusObject
	{
		Q_OBJECT
		Q_PROPERTY(bool mounted READ isMounted NOTIFY mountPointsChanged)
		Q_PROPERTY(QStringList mountPoints READ mountPoints NOTIFY 
				mountPointsChanged)
		/** \brief Available space in mounted filesystem
		 *
		 * \note Filesystem must be mounted
		 * \returns Number of available bytes, or 0 if filesystem is not mounted
		 * or if available space could not be retrieved.
		 */
		Q_PROPERTY(quint64 availableSpace READ availableSpace)
		Q_PROPERTY(QDBusObjectPath blockDevice READ blockDevice)

	signals:
		void mountPointsChanged(const QStringList mountPoints);

	public:
		FileSystem(const QDBusObjectPath &path, QObject *parent = nullptr);
		bool isValid() const override;
		static bool isFileSystem(const QDBusObjectPath &path, int replyTimeout);
		static bool isFileSystem(const QList<QString> &interfaces);

		bool isMounted() const;
		QStringList mountPoints() const;
		quint64 availableSpace() const;
		QDBusObjectPath blockDevice() const;

	public slots:
		void mount() const;
		void unmount(bool force = false) const;

	private slots:
		void inspectFileSysPropertyChanges(const QString &interface, const 
				QVariantMap &changedProperties, const QStringList 
				&invalidatedProperties);
	};
}

QDebug operator <<(QDebug d, const QDrive::FileSystem &fileSystem);
