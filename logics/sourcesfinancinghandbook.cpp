#include "sourcesfinancinghandbook.h"

using namespace logics;

SourcesFinancingHandBook::SourcesFinancingHandBook(QObject *parent)
    : HandBookAbstract(parent)
{}

bool SourcesFinancingHandBook::modelInitialization()
{
    setTable("sources_financing");
    setEditStrategy(QSqlTableModel::OnFieldChange);
    if (!setHeaderData(COLUMN_VALUE_INDEX, Qt::Horizontal, tr("Источники финансирования")) || !select())
    {
        qDebug() << lastError();
        return false;
    }
    initSort();
    return updateMap();
}

void SourcesFinancingHandBook::setApproximateFilter(const QString &value)
{
    if (value.isEmpty())
        setFilter("");
    else
        setFilter(QString("source_financing LIKE '%%1%'").arg(value));
}
