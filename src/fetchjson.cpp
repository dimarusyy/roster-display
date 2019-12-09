#include "fetchjson.h"
#include "config.h"

#include <QCoreApplication>
#include <QNetworkReply>
#include <QThread>
#include <QTextStream>
#include <QDir>

FetchJson::FetchJson(QObject *parent)
    : QObject(parent)
    , _nam(std::make_unique<QNetworkAccessManager>())
{
    qRegisterMetaType<std::shared_ptr<nlohmann::json>>("std::shared_ptr<nlohmann::json>");
}

void FetchJson::fetch(const QUrl& url)
{
    const auto update_cache = [](const QFileInfo& fi, const QByteArray& data){
        // create dir
        if(!fi.dir().exists() && !QDir().mkdir(fi.dir().path()))
        {
            throw std::runtime_error("Faled to create dir:[" + fi.dir().path().toStdString() + "]");
        }

        // remove old file
        QFile(fi.path()).remove();

        // save
        QFile file(fi.filePath());
        qDebug() << "Creating file: [" << fi.filePath() << "]";
        if(file.open(QIODevice::WriteOnly))
        {
            if(-1 == file.write(data))
            {
                throw std::runtime_error("IO(write) failed");
            }
        }
    };

    const auto parse_json = [this, update_cache](const QFileInfo& fi, const QByteArray& data, bool updateCache){
        QThread *thread = QThread::create([this, update_cache, fi, data, updateCache]()
        {
            try {
                auto json = std::make_shared<nlohmann::json>();
                *json = json->parse(data.begin(), data.end()).at("roster");
                if(updateCache) update_cache(fi, data);
                emit succeeded(json);
                qDebug() << "Fetched : [" << json->size() << "] elements";
            } catch (std::exception ex) {
                QString ec ("Failed to parse json [" + QString::fromStdString(ex.what()) + "]");
                emit failed(ec);
                qDebug() << ec;
            }
        }
        );
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        thread->start();
    };

    // check if cached
    const auto roster_file = config::defaultCacheFile();
    if(roster_file.exists())
    {
        const auto rf_ms = static_cast<quint64>(roster_file.lastModified().msecsTo(QDateTime::currentDateTime())); //oh, why signed ??!
        if(rf_ms > config::defaultCacheValidityTimeout_ms())
        {
            qDebug() << "Removing cache and performing full fetch";
            QFile(roster_file.path()).remove();
        }

        qDebug() << "Reading file: [" << roster_file.filePath() << "]";
        QFile file(roster_file.filePath());
        if(file.open(QIODevice::ReadOnly))
        {
            parse_json(roster_file, file.readAll(), false);
            return;
        }
        else
        {
            qDebug() << "Failed to open file [" << roster_file.path() << "]. Performing fetching.";
        }
    }

    QObject::connect(_nam.get(),
                     &QNetworkAccessManager::finished,
                     this,
                     [this, parse_json, roster_file](QNetworkReply* reply)
    {
        // handle error
        const auto ec = reply->error();
        if (ec)
        {
            QString ec("Error while fetching json: [" + reply->errorString() + "]");
            qDebug() << ec;
            emit failed(ec);
            return;
        }

        auto data = reply->readAll();
        parse_json(roster_file, data, true);
    });

    _nam->get(QNetworkRequest(url.isEmpty() ? config::defaultFetchUrl() : url));
}
