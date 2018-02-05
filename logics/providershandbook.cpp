#include "providershandbook.h"

using namespace logics;

ProvidersHandBook::ProvidersHandBook(QObject *parent)
    : HandBookAbstract(parent)
{}

bool ProvidersHandBook::modelInitialization()
{
    setTable("providers");
    setEditStrategy(QSqlTableModel::OnFieldChange);
    if (!setHeaderData(COLUMN_VALUE_INDEX, Qt::Horizontal, tr("Поставщики товаров/Услуг")) || !select())
    {
        qDebug() << lastError();
        return false;
    }
    initSort();
    return updateMap();
}

void ProvidersHandBook::setApproximateFilter(const QString &value)
{
    if (value.isEmpty())
        setFilter("");
    else
        setFilter(QString("provider LIKE '%%1%'").arg(value));
}
