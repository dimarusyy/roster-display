#pragma once

#include <QAbstractListModel>
#include <QStandardItemModel>
#include <QJsonDocument>
#include <QNetworkAccessManager>

#include <3rdparty/nlohmann/json.hpp>
#include "fetchjson.h"

class RosterListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(RosterRoles)
public:
    enum RosterRoles
    {
        AvatarColor = Qt::UserRole + 1,
        FirstName,
        LastName
    };

    RosterListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;    

signals:
    void itemPopulated(int);

public slots:
    void loadFromUrl(const QUrl&);

protected:
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

private:
    FetchJson _fetchJson;
    std::shared_ptr<nlohmann::json> _json{};
    int _fetched{ 0 };    
};
