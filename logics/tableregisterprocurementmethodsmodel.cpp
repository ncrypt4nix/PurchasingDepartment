#include "tableregisterprocurementmethodsmodel.h"

using namespace logics;

TableRegisterProcurementMethodsModel::TableRegisterProcurementMethodsModel(QObject *parent)
    : TableModelAbstract(parent)
{}

bool TableRegisterProcurementMethodsModel::modelInitialization()
{
    if (!setStartQueryState())
        return false;
    setColumnIdNumber(0);
    QStringList columnNames;
    columnNames << tr("№")
                << ProcurementMethodObject::NUMBER_NOTICE_STR
                << ProcurementMethodObject::NOTICE_DATE_STR
                << ProcurementMethodObject::PROCUREMENT_OBJECT_STR
                << ProcurementMethodObject::STARTING_PRICE_STR
                << ProcurementMethodObject::START_DATE_DEADLINE_STR
                << ProcurementMethodObject::END_DATE_DEADLINE_STR
                << ProcurementMethodObject::OPENING_ENVELOPES_DATE_STR
                << ProcurementMethodObject::SUMMARIZING_DATE_STR
                << ProcurementMethodObject::PROCUREMENT_METHODS_STR
                << ProcurementMethodObject::PROCEDURE_COMPLETE_STR
                << ProcurementMethodObject::DATE_REGISTRATION_STR
                << ProcurementMethodObject::SMP_STR
                << ProcurementMethodObject::COMPLETENESS;
    setColumnProcedureCompleteNumber(10);  //номер колонки с статусом
    setColumnSMPNumber(12); //номер колонки с СМП
    setCompletenessNumber(13);

    for (int i = 0; i < columnNames.size(); i++)
        model->setHeaderData(i, Qt::Horizontal, columnNames.at(i));

    return isNotValidLastError("Инициализация модели");
}

bool TableRegisterProcurementMethodsModel::deleteColumn(const QModelIndex &index) const
{
    auto procurementMethodId = index.sibling(index.row(), getColumnIdNumber()).data().toInt();
    QSqlQuery query;
    query.prepare("DELETE FROM register_procurement_methods WHERE register_procurement_method_id = :register_procurement_method_id");
    query.bindValue(":register_procurement_method_id", procurementMethodId);
    query.exec();
    return isNotValidLastError(query, "Ошибка удаления");
}

bool TableRegisterProcurementMethodsModel::setStartQueryState() const
{
    model->setQuery("SELECT reg_proc_meth.register_procurement_method_id,"
                        "reg_proc_meth.number_notice,"
                        "reg_proc_meth.notice_date,"
                        "reg_proc_meth.procurement_object,"
                        "reg_proc_meth.starting_price,"
                        "reg_proc_meth.start_date_deadline,"
                        "reg_proc_meth.end_date_deadline,"
                        "reg_proc_meth.opening_envelopes_date,"
                        "reg_proc_meth.summarizing_date,"
                        "procurement_methods.procurement_method,"
                        "reg_proc_meth.procedure_complete,"
                        "reg_proc_meth.date_registration,"
                        "reg_proc_meth.smp,"
                        "reg_proc_meth.completeness "
                    "FROM register_procurement_methods AS reg_proc_meth "
                    "INNER JOIN procurement_methods "
                    "ON reg_proc_meth.procurement_method_id = procurement_methods.procurement_method_id ");
    return isNotValidLastError("Установка начального состояния модели");
}

uint TableRegisterProcurementMethodsModel::getColumnProcedureCompleteNumber() const
{
    return columnProcedureCompleteNumber;
}

FindObjectAbstract *TableRegisterProcurementMethodsModel::getFindObject()
{
    return new FindObjectProcurementMethod;
}

void TableRegisterProcurementMethodsModel::setColumnProcedureCompleteNumber(const uint &value)
{
    columnProcedureCompleteNumber = value;
}

uint TableRegisterProcurementMethodsModel::getColumnSMPNumber() const
{
    return columnSMPNumber;
}

void TableRegisterProcurementMethodsModel::setColumnSMPNumber(const uint &value)
{
    columnSMPNumber = value;
}

