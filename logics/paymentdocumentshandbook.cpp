#include "paymentdocumentshandbook.h"

using namespace logics;

PaymentDocumentsHandBook::PaymentDocumentsHandBook(QObject *parent)
    : HandBookAbstract(parent)
{}

bool PaymentDocumentsHandBook::modelInitialization()
{
    setTable("payment_documents");
    setEditStrategy(QSqlTableModel::OnFieldChange);
    if (!setHeaderData(COLUMN_VALUE_INDEX, Qt::Horizontal, tr("Платежные документы")) || !select())
    {
        qDebug() << lastError();
        return false;
    }
    initSort();
    return updateMap();
}

void PaymentDocumentsHandBook::setApproximateFilter(const QString &value)
{
    if (value.isEmpty())
        setFilter("");
    else
        setFilter(QString("payment_document LIKE '%%1%'").arg(value));
}
