#pragma once

#include <QUrl>
#include <QFileInfo>

struct config
{
    static const QUrl defaultFetchUrl();
    static const QFileInfo defaultCacheFile();
    static quint64 defaultCacheValidityTimeout_ms();
};
