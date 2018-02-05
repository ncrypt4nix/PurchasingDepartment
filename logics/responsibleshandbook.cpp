#include "responsibleshandbook.h"

using namespace logics;

ResponsiblesHandBook::ResponsiblesHandBook(QObject *parent)
    : HandBookAbstract(parent)
{}

bool ResponsiblesHandBook::modelInitialization()
{
    setTable("responsibles");
    setEditStrategy(QSqlTableModel::OnFieldChange);
    if (!setHeaderData(COLUMN_VALUE_INDEX, Qt::Horizontal, tr("Ответственные лица")) || !select())
    {
        qDebug() << lastError();
        return false;
    }
    initSort();
    return updateMap();
}

void ResponsiblesHandBook::setApproximateFilter(const QString &value)
{
    if (value.isEmpty())
        setFilter("");
    else
        setFilter(QString("responsible LIKE '%%1%'").arg(value));
}
