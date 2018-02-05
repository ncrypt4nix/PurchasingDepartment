#include "database.h"

using namespace logics;

const QString DataBase::DATABASE_DRV = "QMYSQL";
const QString DataBase::DATABASE_NAME = "registry";

QString DataBase::userName = "";
QString DataBase::hostName = "";
QString DataBase::password = "";

DataBase::DataBase(QObject *parent)
    : QObject(parent)
{}

bool DataBase::createConnection()
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase(DATABASE_DRV));
    db->setDatabaseName(DATABASE_NAME);
    db->setUserName(userName);
    db->setHostName(hostName);
    db->setPassword(password);
    if (!db->open())
    {
        qDebug() << "Ошибка открытия БД: " << db->lastError();
        return false;
    }
    return true;
}

QString DataBase::getUserName()
{
    return userName;
}

QString DataBase::getHostName()
{
    return hostName;
}

QString DataBase::getPassword()
{
    return password;
}

void DataBase::setPassword(const QString &value)
{
    password = value;
}

void DataBase::setHostName(const QString &value)
{
    hostName = value;
}

void DataBase::setUserName(const QString &value)
{
    userName = value;
}
