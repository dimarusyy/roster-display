#include "rosterlistmodel.h"

#include <QNetworkReply>
#include <3rdparty/nlohmann/json.hpp>

static constexpr std::size_t ROSTER_FETCH_SIZE = 100;

RosterListModel::RosterListModel(QObject* parent)
    : QAbstractListModel(parent)
    , _fetchJson(parent)
{
    _fetchJson.fetch({});
}

int RosterListModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : _fetched;
}

QVariant RosterListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return {};

    if (static_cast<std::size_t>(index.row()) >= _json.size() || index.row() < 0)
        return {};

    const auto it = _json.begin() + index.row();
    if (role == RosterRoles::AvatarColor)
    {
        const auto sex = it->at("account").at("sex").get<std::string>();
        return sex == "MALE" ? "#B5E6FF" : (sex == "FEMALE" ? "#FCD0FC" : "#E1E8ED");
    }
    else if (role == RosterRoles::FirstName)
    {
        return QString::fromStdString(it->at("account").at("firstName").get<std::string>());
    }
    else if (role == RosterRoles::LastName)
    {
        return QString::fromStdString(it->at("account").at("lastName").get<std::string>());
    }
    else return {};
}

QHash<int, QByteArray> RosterListModel::roleNames() const
{
    return
    {
        {RosterRoles::AvatarColor, "avatarColor" },
        {RosterRoles::FirstName, "firstName" },
        {RosterRoles::LastName, "lastName" },
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
    return static_cast<std::size_t>(_fetched) < _json.size();
}

void RosterListModel::fetchMore(const QModelIndex& parent)
{
    if (parent.isValid())
        return;

    const auto to_fetch = std::min(ROSTER_FETCH_SIZE, _json.size() - static_cast<std::size_t>(_fetched));
    if (to_fetch <= 0)
    {
        qDebug() << "No items to fetch";
        return;
    }

    beginInsertRows(QModelIndex(), _fetched, _fetched + static_cast<decltype(_fetched)>(to_fetch) - 1);
    _fetched += to_fetch;
    endInsertRows();

    emit itemPopulated(static_cast<decltype(_fetched)>(to_fetch));
}

bool RosterListModel::event(QEvent* event)
{
    if (event->type() == QEvent::User + 1)
    {
        auto& json = static_cast<FetchJsonEvent*>(event)->data();
        beginResetModel();
        _json.swap(json);
        endResetModel();
        return true;
    }

    return QAbstractListModel::event(event);
}
