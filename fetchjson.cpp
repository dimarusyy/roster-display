#include "fetchjson.h"

#include <QCoreApplication>
#include <QThread>

namespace {
    static constexpr auto ROSTER_GROUPORDER_ID = "groupOrder";
    static constexpr auto ROSTER_GROUP_ID = "group";
}

const QUrl FetchJson::defaultUrl{"https://file.wowapp.me/owncloud/index.php/s/sGOXibS0ZSspQE8/download"};

FetchJson::FetchJson(QObject *parent)
    : QObject(parent)
    , _nam(std::make_unique<QNetworkAccessManager>())
{       
}

void FetchJson::fetch(const QUrl& url)
{
    QObject::connect(_nam.get(),
                     &QNetworkAccessManager::finished,
                     this,
                     [this](QNetworkReply* reply)
    {
        // handle error
        auto ec = reply->error();
        if (ec)
        {
            qDebug() << reply->errorString();
            QCoreApplication::postEvent(this, new FetchJsonEvent(nullptr));
            return;
        }

        QThread *thread = QThread::create([=]
        {
            QByteArray result = reply->readAll();

            auto json = nlohmann::json::parse(result.begin(), result.end()).at("roster");
            std::sort(json.begin(),
                      json.end(),
                      [](decltype(*json.begin()) lhs, decltype(*json.begin()) rhs)
            {
                const auto lhs_groupOrder = lhs[ROSTER_GROUPORDER_ID].get<int>();
                const auto rhs_groupOrder = rhs[ROSTER_GROUPORDER_ID].get<int>();

                const auto lhs_group = lhs[ROSTER_GROUP_ID].get<std::string>();
                const auto rhs_group = rhs[ROSTER_GROUP_ID].get<std::string>();

                return lhs_groupOrder < rhs_groupOrder ||
                        (!(lhs_groupOrder < rhs_groupOrder) && lhs_group < rhs_group);
            });

            QCoreApplication::postEvent(this, new FetchJsonEvent(std::move(json)));
        });
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        thread->start();
    });

    _nam->get(QNetworkRequest(url.isEmpty() ? defaultUrl : url));
}