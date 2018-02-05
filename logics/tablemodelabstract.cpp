#include "tablemodelabstract.h"

using namespace logics;

TableModelAbstract::TableModelAbstract(QObject *parent)
    : QObject(parent)
{
    model = new QSqlQueryModel(this);
}

QSqlQueryModel *TableModelAbstract::getModel() const
{
    return model;
}

bool TableModelAbstract::findQuery(FindObjectAbstract *findObj)
{
    model->setQuery(findObj->getFindQuery());
    return isNotValidLastError("Запрос поиска");
}

bool TableModelAbstract::updateModel() const
{
    model->setQuery(model->query().lastQuery());
    return isNotValidLastError("Обновление модели");
}

bool TableModelAbstract::isNotValidLastError(const QString &operation) const
{
    if (model->lastError().isValid())
    {
        qDebug() << operation << ": " << model->lastError();
        return false;
    }
    return true;
}

bool TableModelAbstract::isNotValidLastError(const QSqlQuery &query, const QString &operation) const
{
    if (query.lastError().isValid())
    {
        qDebug() << operation << ": " << query.lastError();
        return false;
    }
    return true;
}

uint TableModelAbstract::getColumnIdNumber() const
{
    return columnIdNumber;
}

void TableModelAbstract::setColumnIdNumber(const uint &value)
{
    columnIdNumber = value;
}

uint TableModelAbstract::getCompletenessNumber() const
{
    return completenessNumber;
}

void TableModelAbstract::setCompletenessNumber(const uint &value)
{
    completenessNumber = value;
}

