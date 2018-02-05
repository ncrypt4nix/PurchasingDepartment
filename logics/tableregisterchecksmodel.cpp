#include "tableregisterchecksmodel.h"

using namespace logics;

TableRegisterChecksModel::TableRegisterChecksModel(QObject *parent)
    : TableModelAbstract(parent)
{}

bool TableRegisterChecksModel::modelInitialization()
{
    if (!setStartQueryState())
        return false;
    setColumnIdNumber(0);
    QStringList columnNames;
    columnNames << tr("№")
                 << logics::CheckObject::CHECK_NUMBER_STR
                 << logics::CheckObject::PAYMENT_DOCUMENTS_STR
                 << logics::CheckObject::REGISTRATION_DATE_STR
                 << logics::CheckObject::CHECK_DATE_STR
                 << logics::CheckObject::CHECK_SUM_STR
                 << logics::CheckObject::DESCRIPTION_STR
                 << logics::CheckObject::NUMBER_CHECKS_STR
                 << logics::CheckObject::PROVIDERS_STR
                 << logics::CheckObject::SUBDIVISIONS_STR
                 << logics::CheckObject::RESPONSIBLES_STR
                 << logics::CheckObject::SOURCE_FINANCINGS_STR
                 << logics::CheckObject::COMPLETENESS;

    setCompletenessNumber(12);

    for (int i = 0; i < columnNames.size(); i++)
        model->setHeaderData(i, Qt::Horizontal, columnNames.at(i));

    return isNotValidLastError("Инициализация модели");
}

bool TableRegisterChecksModel::deleteColumn(const QModelIndex &index) const
{
    auto checkId = index.sibling(index.row(), getColumnIdNumber()).data().toInt();
    QSqlQuery query;
    query.prepare("DELETE FROM register_checks WHERE check_id = :check_id");
    query.bindValue(":check_id", checkId);
    query.exec();
    return isNotValidLastError(query, "Ошибка удаления");
}

bool TableRegisterChecksModel::setStartQueryState() const
{
    model->setQuery("SELECT checks.check_id,"
                        "checks.check_number,"
                        "payment_documents.payment_document,"
                        "checks.registration_date,"
                        "checks.check_date,"
                        "checks.check_sum,"
                        "checks.description,"
                        "checks.number_checks,"
                        "providers.provider,"
                        "subdivisions.subdivision,"
                        "responsibles.responsible,"
                        "sources_financing.source_financing,"
                        "completeness "
                    "FROM register_checks AS checks "
                    "INNER JOIN providers "
                    "ON checks.provider_id = providers.provider_id "
                    "INNER JOIN subdivisions "
                    "ON checks.subdivision_id = subdivisions.subdivision_id "
                    "INNER JOIN responsibles "
                    "ON checks.responsible_id = responsibles.responsible_id "
                    "INNER JOIN sources_financing "
                    "ON checks.source_financing_id = sources_financing.source_financing_id "
                    "INNER JOIN payment_documents "
                    "ON checks.payment_document_id = payment_documents.payment_document_id;");
    return isNotValidLastError("Установка начального состояния модели");
}

FindObjectAbstract *TableRegisterChecksModel::getFindObject()
{
    return new FindObjectCheck;
}

