#include "rosterlistmodel.h"

#include <QNetworkReply>
#include <3rdparty/nlohmann/json.hpp>

#include <iterator>

static constexpr std::size_t ROSTER_FETCH_SIZE = 10;

RosterListModel::RosterListModel(QObject* parent)
    : QAbstractListModel(parent)
    , _fetchJson(parent)
    , _json(std::make_shared<nlohmann::json>())
{
    QObject::connect(&_fetchJson, &FetchJson::succeeded, this, [this](std::shared_ptr<nlohmann::json> json)
    {
        QAbstractListModel::beginResetModel();
        _json = json;
        QAbstractListModel::endResetModel();

        emit loaded();
    }, Qt::QueuedConnection);

    _fetchJson.fetch({});
    emit loading();
}

int RosterListModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : _fetched;
}

QVariant RosterListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return {};

    if (static_cast<std::size_t>(index.row()) >= _json->size() || index.row() < 0)
        return {};

    QVariant rc{};
    const auto it = _json->begin() + index.row();
    const auto account = it->at("account");
    if (role == RosterRoles::AvatarColor)
    {
        const auto sex = account.value("sex", "");
        rc = (sex == "MALE" ? "#B5E6FF" : (sex == "FEMALE" ? "#FCD0FC" : "#E1E8ED"));
    }
    else if (role == RosterRoles::FirstName)
    {
        rc = QString::fromStdString(account.value("firstName", ""));
    }
    else if (role == RosterRoles::LastName)
    {
        rc = QString::fromStdString(account.value("lastName", ""));
    }
    else if (role == RosterRoles::UserName)
    {
        rc = QString::fromStdString(account.value("username",""));
    }
    else if (role == RosterRoles::Sex)
    {
        rc = QString::fromStdString(account.value("sex", ""));
    }
    else if (role == RosterRoles::Country)
    {
        rc = QString::fromStdString(account.value("country", ""));
    }
    else if (role == RosterRoles::Birthday)
    {
        if(account.contains("birthday"))
        {
            auto since_epoch = account.at("birthday").get<qint64>();
            auto bd = QDateTime::fromMSecsSinceEpoch(since_epoch);
            rc = bd.toString();
        }
    }
    else if (role == RosterRoles::Language)
    {
        rc = QString::fromStdString(account.value("language", ""));
    }
    else if (role == RosterRoles::Group)
    {
        rc = QString::fromStdString(it->at("group").get<std::string>());
    }
    else if (role == RosterRoles::GroupOrder)
    {
        rc = it->at("groupOrder").get<uint>();
    }

    return rc;
}

QHash<int, QByteArray> RosterListModel::roleNames() const
{
    return
    {
        {RosterRoles::AvatarColor, "avatarColor" },
        {RosterRoles::FirstName, "firstName" },
        {RosterRoles::LastName, "lastName" },
        {RosterRoles::UserName, "userName" },
        {RosterRoles::Sex, "sex" },
        {RosterRoles::Country, "country" },
        {RosterRoles::Birthday, "birthday" },
        {RosterRoles::Language, "language" },
        {RosterRoles::Group, "group" },
        {RosterRoles::GroupOrder, "groupOrder" }
    };
}

void RosterListModel::loadFromUrl(const QUrl& url)
{
    _fetchJson.fetch(url);
}

bool RosterListModel::canFetchMore(const QModelIndex& parent) const
{
    if (parent.isValid())
        return false;
    return static_cast<std::size_t>(_fetched) < _json->size();
}

void RosterListModel::fetchMore(const QModelIndex& parent)
{
    if (parent.isValid())
        return;

    const auto to_fetch = std::min(ROSTER_FETCH_SIZE, _json->size() - static_cast<std::size_t>(_fetched));
    if (to_fetch <= 0)
    {
        qDebug() << "No items to fetch";
        return;
    }

    beginInsertRows(QModelIndex(), _fetched, _fetched + static_cast<decltype(_fetched)>(to_fetch) - 1);
    _fetched += to_fetch;
    endInsertRows();

    emit itemsPopulated(static_cast<decltype(_fetched)>(to_fetch));
}
