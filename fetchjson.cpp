#include "fetchjson.h"

#include <QCoreApplication>
#include <QThread>

const QUrl FetchJson::defaultUrl{"https://file.wowapp.me/owncloud/index.php/s/sGOXibS0ZSspQE8/download"};

FetchJson::FetchJson(QObject *parent)
    : QObject(parent)
    , _nam(std::make_unique<QNetworkAccessManager>())
{
    qRegisterMetaType<std::shared_ptr<nlohmann::json>>("std::shared_ptr<nlohmann::json>");
}

void FetchJson::fetch(const QUrl& url)
{
    QObject::connect(_nam.get(),
                     &QNetworkAccessManager::finished,
                     this,
                     [this](QNetworkReply* reply)
    {
        // handle error
        const auto ec = reply->error();
        if (ec)
        {
            qDebug() << reply->errorString();
            emit failed(ec);
            return;
        }

        const QByteArray result = reply->readAll();
        QThread *thread = QThread::create([this, result]()
        {
            auto json = std::make_shared<nlohmann::json>();
            *json = json->parse(result.begin(), result.end()).at("roster");
            qDebug() << "Fetched : [" << json->size() << "] elements";
            emit succeeded(json);
        }
        );
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        thread->start();
    });

    _nam->get(QNetworkRequest(url.isEmpty() ? defaultUrl : url));
}
