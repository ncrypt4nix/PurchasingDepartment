#include "informationendcontracts.h"

using namespace logics;

QVector<uint> InformationEndContracts::idVector = {};
QVector<uint> InformationEndContracts::idDeleted = {};

InformationEndContracts::InformationEndContracts(QObject *parent) :
    QObject(parent)
{}

bool InformationEndContracts::checkId(const uint &id)
{
    QVector<uint>::iterator it = qFind(idVector.begin(), idVector.end(), id);
    return it != idVector.end();
}

bool InformationEndContracts::deletedId(const uint &id)
{
    QVector<uint>::iterator it = qFind(idDeleted.begin(), idDeleted.end(), id);
    return it != idDeleted.end();
}

void InformationEndContracts::addId(const uint &id)
{
    idVector.push_back(id);
    qSort(idVector);
}

void InformationEndContracts::deleteId(const uint &id)
{
    QVector<uint>::iterator it = qFind(idVector.begin(), idVector.end(), id);
    if (it == idVector.end())
        return;
    idVector.erase(it);
    idDeleted.push_back(id);
    qSort(idDeleted);
}

bool InformationEndContracts::save()
{
    QFile fileInfo(getFilePathInfo());
    if (!fileInfo.open(QIODevice::WriteOnly))
        return false;
    for (auto id : idVector)
        fileInfo.write(QString::number(id).toStdString().c_str(), sizeof(uint));
    fileInfo.close();

    QFile fileDeleted(getFilePathDeleted());
    if (!fileDeleted.open(QIODevice::WriteOnly))
        return false;
    for (auto id : idDeleted)
        fileDeleted.write(QString::number(id).toStdString().c_str(), sizeof(uint));
    fileDeleted.close();

    return true;
}

bool InformationEndContracts::read()
{
    QFile fileInfo(getFilePathInfo());
    if (!fileInfo.open(QIODevice::ReadOnly))
        return false;
    char temp[1024];
    while (!fileInfo.atEnd())
    {
        fileInfo.read(temp, sizeof(uint));
        idVector.push_back(QString(temp).toUInt());
    }
    fileInfo.close();

    QFile fileDeleted(getFilePathDeleted());
    if (!fileDeleted.open(QIODevice::ReadOnly))
        return false;
    while (!fileDeleted.atEnd())
    {
        fileDeleted.read(temp, sizeof(uint));
        idDeleted.push_back(QString(temp).toUInt());
    }
    fileDeleted.close();

    return true;
}

QString InformationEndContracts::getFilePathInfo()
{
    QDir currentDir = QDir::current();
    QString serviceDir = "service";
    if (!currentDir.cd(serviceDir))
    {
        if (!currentDir.mkdir(serviceDir))
            return QString();
        currentDir.cd(serviceDir);
    }
    return currentDir.filePath("info_end_contracts");
}

QString InformationEndContracts::getFilePathDeleted()
{
    QDir currentDir = QDir::current();
    QString serviceDir = "service";
    if (!currentDir.cd(serviceDir))
    {
        if (!currentDir.mkdir(serviceDir))
            return QString();
        currentDir.cd(serviceDir);
    }
    return currentDir.filePath("info_end_contracts_deleted");
}
