/**
 * \author Andreas Misje
 * \date 2014
 * \copyright MIT
 */

#include "AvailableSpace.h"
#include <sys/statvfs.h>

quint64 QDrive::availableSpace(const QByteArray &fileSystemPath)
{
	struct statvfs stat;
	if (statvfs(fileSystemPath.constData(), &stat))
		return 0;

	return static_cast<quint64>(stat.f_bavail) * stat.f_frsize;
}

quint64 QDrive::totalSpace(const QByteArray &fileSystemPath)
{
	struct statvfs stat;
	if (statvfs(fileSystemPath.constData(), &stat))
		return 0;

	return static_cast<quint64>(stat.f_blocks) * stat.f_frsize;
}
