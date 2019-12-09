#include "config.h"

#include <QCoreApplication>
#include <QDir>

const QUrl config::defaultFetchUrl()
{
    return QUrl{"https://file.wowapp.me/owncloud/index.php/s/sGOXibS0ZSspQE8/download"};
}

const QFileInfo config::defaultCacheFile()
{
    return QFileInfo(QDir(QCoreApplication::applicationDirPath() +  QDir::separator() + "data"), "roster.json");
}

quint64 config::defaultCacheValidityTimeout_ms()
{
    return 60*60*1000; // 1hour
}
