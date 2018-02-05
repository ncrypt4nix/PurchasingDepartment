#include "procurementmethodshandbook.h"

using namespace logics;

ProcurementMethodsHandBook::ProcurementMethodsHandBook(QObject *parent)
    : HandBookAbstract(parent)
{}

bool ProcurementMethodsHandBook::modelInitialization()
{
    setTable("procurement_methods");
    setEditStrategy(QSqlTableModel::OnFieldChange);
    if (!setHeaderData(COLUMN_VALUE_INDEX, Qt::Horizontal, tr("Способы закупки")) || !select())
    {
        qDebug() << lastError();
        return false;
    }
    initSort();
    return updateMap();
}

void ProcurementMethodsHandBook::setApproximateFilter(const QString &value)
{
    if (value.isEmpty())
        setFilter("");
    else
        setFilter(QString("procurement_method LIKE '%%1%'").arg(value));
}
