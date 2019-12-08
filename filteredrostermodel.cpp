#include "filteredrostermodel.h"

FilteredRosterModel::FilteredRosterModel(QObject* parent)
    : QSortFilterProxyModel(parent)
    , _rosterListModel(parent)
{
    QObject::connect(&_rosterListModel, &RosterListModel::loading, this, &FilteredRosterModel::loading);
    QObject::connect(&_rosterListModel, &RosterListModel::loaded, this, &FilteredRosterModel::loaded);

    setSourceModel(&_rosterListModel);

    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortingColumn(RosterListModel::GroupOrder);
    sort(0);
}

void FilteredRosterModel::setFilter(const QString& filter)
{
    setFilterFixedString(filter);
    sort(0);
}

void FilteredRosterModel::setSortingColumn(int role)
{
    setFilterRole(static_cast<RosterListModel::RosterRoles>(role));
    setSortRole(static_cast<RosterListModel::RosterRoles>(role));
    sort(0);
}
