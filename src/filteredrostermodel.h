#pragma once

#include "rosterlistmodel.h"

#include <QSortFilterProxyModel>

class FilteredRosterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    FilteredRosterModel(QObject* parent = nullptr);

    Q_INVOKABLE void setFilter(const QString&);
    Q_INVOKABLE void setSortingColumn(int role);

signals:
    void loading();
    void loaded();

private:
    RosterListModel _rosterListModel;
};

