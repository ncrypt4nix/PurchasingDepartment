#include "handbookabstract.h"

using namespace logics;

const int HandBookAbstract::COLUMN_ID_INDEX = 0;
const int HandBookAbstract::COLUMN_VALUE_INDEX = 1;

HandBookAbstract::HandBookAbstract(QObject *parent)
    : QSqlTableModel(parent)
{}

bool HandBookAbstract::updateMap()
{
    mapHandBook.clear();
    QSqlQuery query;
    QSqlRecord record = this->record();
    QString idName = record.fieldName(COLUMN_ID_INDEX),
            valueName = record.fieldName(COLUMN_VALUE_INDEX);
    QString queryStr = "SELECT %1, %2 FROM %3;";
    queryStr = queryStr.arg(idName)
            .arg(valueName)
            .arg(tableName());
    if (!query.exec(queryStr))
    {
        qDebug() << query.lastError();
        return false;
    }
    record = query.record();
    while (query.next())
        mapHandBook[query.value(record.indexOf(valueName)).toString()]
                = query.value(record.indexOf(idName)).toInt();   
    emit mapHandBookChanged();
    return true;
}

QMap<QString, uint> HandBookAbstract::getMapHandBook()
{
    return mapHandBook;
}

void HandBookAbstract::initSort()
{
    setSort(COLUMN_VALUE_INDEX, Qt::AscendingOrder);
    sort(COLUMN_VALUE_INDEX, Qt::AscendingOrder);
}
