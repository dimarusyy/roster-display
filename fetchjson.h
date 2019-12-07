#ifndef FETCHJSON_H
#define FETCHJSON_H

#include <QObject>
#include <QNetworkReply>
#include <QEvent>

#include <3rdparty/nlohmann/json.hpp>

class FetchJsonEvent : public QEvent
{
public:
    FetchJsonEvent(nlohmann::json&& json)
        : QEvent(QEvent::Type(QEvent::User + 1))
        , _json(json)
    {
    }

    auto& data()
    {
        return _json;
    }

private:
    nlohmann::json _json;
};

class FetchJson : public QObject
{
    Q_OBJECT
public:
    static const QUrl defaultUrl;

    explicit FetchJson(QObject *parent = nullptr);
    void fetch(const QUrl&);

public slots:

private:
    std::unique_ptr<QNetworkAccessManager> _nam;
};

#endif // FETCHJSON_H
