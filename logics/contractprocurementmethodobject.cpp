#include "contractprocurementmethodobject.h"

using namespace logics;

const QString ContractProcurementMethodObject::REGISTER_PROCUREMENT_METHODS = "contracts_register_procurement_methods";
const QString ContractProcurementMethodObject::REGISTER_PROCUREMENT_METHODS_CHECKS = "checks_register_procurement_methods";

ContractProcurementMethodObject::ContractProcurementMethodObject(QObject *parent)
    : ContractObject(parent)
{
    setRegisterName(REGISTER_PROCUREMENT_METHODS);
    setCheckTableName(REGISTER_PROCUREMENT_METHODS_CHECKS);
}

uint ContractProcurementMethodObject::getRegisterProcurementMethodId() const
{
    return registerProcurementMethodId;
}

bool ContractProcurementMethodObject::setRegisterProcurementMethodId(const uint &value)
{
    registerProcurementMethodId = value;
    QSqlQuery query;
    if (!query.exec("SELECT contract_id FROM " + getRegisterName() +
                    " WHERE register_procurement_method_id = " + QString::number(registerProcurementMethodId)))
    {
        qDebug() << query.lastError();
        return false;
    }
    QSqlRecord record = query.record();
    if (!query.next())
        return false;
    else
        return changeId(query.value(record.indexOf("contract_id")).toUInt());
}

bool ContractProcurementMethodObject::add()
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + getRegisterName() + " "
                  "(contract_number, contracts_sum, start_date, end_date, provider_id,"
                  "subdivision_id, responsible_id, source_financing_id, comment, register_procurement_method_id) "
                  "VALUES (:contract_number, :contracts_sum, :start_date, :end_date, :provider_id,"
                  ":subdivision_id, :responsible_id, :source_financing_id, :comment, :register_procurement_method_id)"
                );
    query.bindValue(":contract_number", getNumber());
    query.bindValue(":contracts_sum", getSum());
    query.bindValue(":start_date", getStartDate());
    query.bindValue(":end_date", getEndDate());
    query.bindValue(":provider_id", getProviderId());
    query.bindValue(":subdivision_id", getSubdivisionId());
    query.bindValue(":responsible_id", getResponsibleId());
    query.bindValue(":source_financing_id", getSourceFinancingId());
    query.bindValue(":comment", getComment());
    query.bindValue(":register_procurement_method_id", registerProcurementMethodId);
    if (!query.exec())
    {
        qDebug() << query.lastError();
        return false;
    }
    id = query.lastInsertId().toUInt();
    return true;
}

ContractProcurementMethodObject &ContractProcurementMethodObject::operator=(const ContractProcurementMethodObject &other)
{
    if (this == &other)
        return *this;
    copyData(other);
    return *this;
}

void ContractProcurementMethodObject::copyData(const ContractProcurementMethodObject &other)
{
    ContractObject::copyData(other);
    registerProcurementMethodId = other.registerProcurementMethodId;
}

