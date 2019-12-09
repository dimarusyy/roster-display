#pragma once

#include <QObject>
#include <QMetaType>
#include <QNetworkAccessManager>

#include <3rdparty/nlohmann/json.hpp>

Q_DECLARE_METATYPE(std::shared_ptr<nlohmann::json>)

class FetchJson : public QObject
{
    Q_OBJECT
public:
    static const QUrl defaultUrl;

    explicit FetchJson(QObject *parent = nullptr);
    void fetch(const QUrl&);

signals:
    void failed(const QString& ec);
    void succeeded(std::shared_ptr<nlohmann::json>);

public slots:

private:
    std::unique_ptr<QNetworkAccessManager> _nam;
};
