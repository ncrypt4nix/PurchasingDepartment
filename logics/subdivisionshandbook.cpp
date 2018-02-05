#include "subdivisionshandbook.h"

using namespace logics;

SubdivisionsHandBook::SubdivisionsHandBook(QObject *parent)
    : HandBookAbstract(parent)
{}

bool SubdivisionsHandBook::modelInitialization()
{
    setTable("subdivisions");
    setEditStrategy(QSqlTableModel::OnFieldChange);
    if (!setHeaderData(COLUMN_VALUE_INDEX, Qt::Horizontal, tr("Подразделение-заказчик")) || !select())
    {
        qDebug() << lastError();
        return false;
    }
    initSort();
    return updateMap();
}

void SubdivisionsHandBook::setApproximateFilter(const QString &value)
{
    if (value.isEmpty())
        setFilter("");
    else
        setFilter(QString("subdivision LIKE '%%1%'").arg(value));
}
