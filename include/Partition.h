/**
 * \author Andreas Misje
 * \date 2014
 * \copyright MIT
 */

#ifndef PARTITION_H
#define PARTITION_H

#include "DBusObject.h"
#include <QDebug>

namespace QDrive
{
	class Partition : public DBusObject
	{
		Q_OBJECT
		Q_PROPERTY(int partitionNumber READ partitionNumber CONSTANT);
		Q_PROPERTY(qulonglong offset READ offset CONSTANT)
		Q_PROPERTY(QString type READ type CONSTANT)
		Q_PROPERTY(bool hasFileSystem READ hasFileSystem CONSTANT)
		Q_PROPERTY(QDBusObjectPath fileSystem READ fileSystem CONSTANT)

	public:
		Partition(const QDBusObjectPath &path, QObject *parent = NULL);

		/** \brief Test whether object is a partition by calling isPartition()
		 * */
		bool isValid() const override;
		static bool isPartition(const QDBusObjectPath &path, int replyTimeout);
		static bool isPartition(const QList<QString> &interfaces);

		int partitionNumber() const;
		qulonglong offset() const;
		/** Partition type
		 *
		 * For DOS partition tables, the string is a hexadecimal number (see
		 * https://en.wikipedia.org/wiki/Partition_type).
		 * For GPT partition tables, the string is a UUID (see
		 * https://en.wikipedia.org/wiki/GUID_Partition_Table)
		 */
		QString type() const;
		QDBusObjectPath blockDevice() const;
		bool hasFileSystem() const;
		QDBusObjectPath fileSystem() const;
	};
};

QDebug operator <<(QDebug d, const QDrive::Partition &partition);

#endif // PARTITION_H
