/**
 * \author Andreas Misje
 * \date 2014
 * \copyright MIT
 */

#include "AvailableSpace.h"
#include <sys/statvfs.h>

quint64 QDrive::availableSpace(const QString &fileSystemPath)
{
	QByteArray rawPath = fileSystemPath.toUtf8();
	struct statvfs stat;
	if (statvfs(rawPath.constData(), &stat))
		return 0;

	return static_cast<quint64>(stat.f_bavail) * stat.f_frsize;
}

quint64 QDrive::totalSpace(const QString &fileSystemPath)
{
	QByteArray rawPath = fileSystemPath.toUtf8();
	struct statvfs stat;
	if (statvfs(rawPath.constData(), &stat))
		return 0;

	return static_cast<quint64>(stat.f_blocks) * stat.f_frsize;
}
