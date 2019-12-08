#pragma once

#include <QObject>
#include <QDebug>

class RosterDetails : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName MEMBER _userName)
    Q_PROPERTY(QString firstName MEMBER _firstName)
    Q_PROPERTY(QString lastName MEMBER _lastName)
    Q_PROPERTY(QString sex MEMBER _sex)
    Q_PROPERTY(QString country MEMBER _country)
    Q_PROPERTY(QString language MEMBER _language)
    Q_PROPERTY(QString birthday MEMBER _birthday)

public:
    explicit RosterDetails(QObject* parent = nullptr) : QObject(parent) {}

    QString _userName{};
    QString _firstName{};
    QString _lastName{};
    QString _sex{};
    QString _country{};
    QString _language{};
    QString _birthday{};
};

Q_DECLARE_METATYPE(RosterDetails*);
