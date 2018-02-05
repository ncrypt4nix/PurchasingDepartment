#include "findobjectcontract.h"

using namespace logics;

FindObjectContract::FindObjectContract(QObject *parent) :
    FindObjectAbstract(parent)
{}

QString FindObjectContract::getFindQuery() const
{
    QString query = "SELECT contracts.contract_id,"
                            "contracts.contract_number,"
                            "contracts.contracts_sum,"
                            "SUM(checks.check_sum) mastered,"   //Освоенно
                            "(contracts.contracts_sum - SUM(checks.check_sum)) residue,"    //Остаток
                            "contracts.start_date,"
                            "contracts.end_date,"
                            "contracts.conclusion_date,"
                            "contracts.date_registration,"
                            "providers.provider,"
                            "sources_financing.source_financing,"
                            "subdivisions.subdivision,"
                            "responsibles.responsible,"
                            "contracts.completeness,"
                            "contracts.comment "
                    "FROM register_contracts AS contracts "
                    "INNER JOIN providers "
                    "ON contracts.provider_id = providers.provider_id "

                    "INNER JOIN subdivisions "
                    "ON contracts.subdivision_id = subdivisions.subdivision_id "
                    "INNER JOIN responsibles "
                    "ON contracts.responsible_id = responsibles.responsible_id "
                    "INNER JOIN sources_financing "
                    "ON contracts.source_financing_id = sources_financing.source_financing_id "

                    "LEFT JOIN checks_register_contracts AS checks "
                    "ON contracts.contract_id = checks.contract_id "
                    "WHERE ";
    if (contractNumber.isChanged())
        query += QString("contracts.contract_number LIKE '%%1%' AND ").arg(contractNumber.getFindValue().toString());
    if (contractsSumFrom.isChanged() && contractsSumTo.isChanged())
        query += QString("contracts.contracts_sum BETWEEN %1 AND %2 AND ")
                .arg(contractsSumFrom.getFindValue().toDouble())
                .arg(contractsSumTo.getFindValue().toDouble());
    else if (contractsSumFrom.isChanged())
        query += QString("contracts.contracts_sum >= %1 AND ").arg(contractsSumFrom.getFindValue().toDouble());
    else if (contractsSumTo.isChanged())
        query += QString("contracts.contracts_sum <= %1 AND ").arg(contractsSumTo.getFindValue().toDouble());
    if (startDateFrom.isChanged() && startDateTo.isChanged())
        query += QString("contracts.start_date BETWEEN '%1' AND '%2' AND ")
                .arg(startDateFrom.getFindValue().toString())
                .arg(startDateTo.getFindValue().toString());
    else if (startDateFrom.isChanged())
        query += QString("contracts.start_date >= '%1' AND ").arg(startDateFrom.getFindValue().toString());
    else if (startDateTo.isChanged())
        query += QString("contracts.start_date <= '%1' AND ").arg(startDateTo.getFindValue().toString());
    if (endDateFrom.isChanged() && endDateTo.isChanged())
        query += QString("contracts.end_date BETWEEN '%1' AND '%2' AND ")
                .arg(endDateFrom.getFindValue().toString())
                .arg(endDateTo.getFindValue().toString());
    else if (endDateFrom.isChanged())
        query += QString("contracts.end_date >= '%1' AND ").arg(endDateFrom.getFindValue().toString());
    else if (endDateTo.isChanged())
        query += QString("contracts.end_date <= '%1' AND ").arg(endDateTo.getFindValue().toString());
    if (conclusionDateFrom.isChanged() && conclusionDateTo.isChanged())
        query += QString("contracts.conclusion_date BETWEEN '%1' AND '%2' AND ")
                .arg(conclusionDateFrom.getFindValue().toString())
                .arg(conclusionDateTo.getFindValue().toString());
    else if (conclusionDateFrom.isChanged())
        query += QString("contracts.conclusion_date >= '%1' AND ").arg(conclusionDateFrom.getFindValue().toString());
    else if (conclusionDateTo.isChanged())
        query += QString("contracts.conclusion_date <= '%1' AND ").arg(conclusionDateTo.getFindValue().toString());
    if (registrationDateFrom.isChanged() && registrationDateTo.isChanged())
        query += QString("contracts.date_registration BETWEEN '%1' AND '%2' AND ")
                .arg(registrationDateFrom.getFindValue().toString())
                .arg(registrationDateTo.getFindValue().toString());
    else if (registrationDateFrom.isChanged())
        query += QString("contracts.date_registration >= '%1' AND ").arg(registrationDateFrom.getFindValue().toString());
    else if (registrationDateTo.isChanged())
        query += QString("contracts.date_registration <= '%1' AND ").arg(registrationDateTo.getFindValue().toString());
    if (providerId.isChanged())
        query += QString("contracts.provider_id = %1 AND ").arg(providerId.getFindValue().toUInt());
    if (subdivisionId.isChanged())
        query += QString("contracts.subdivision_id = %1 AND ").arg(subdivisionId.getFindValue().toUInt());
    if (responsibleId.isChanged())
        query += QString("contracts.responsible_id = %1 AND ").arg(responsibleId.getFindValue().toUInt());
    if (sourceFinancingId.isChanged())
        query += QString("contracts.source_financing_id = %1 AND ").arg(sourceFinancingId.getFindValue().toUInt());
    if (completeness.isChanged())
        query += QString("contracts.completeness = %1 AND ").arg(completeness.getFindValue().toBool());
    if (comment.isChanged())
        query += QString("contracts.comment LIKE '%%1%' AND ").arg(comment.getFindValue().toString());
    query.remove(query.lastIndexOf("AND"), 3);
    query += "GROUP BY contracts.contract_id;";
    return query;
}

void FindObjectContract::setContractNumber(const QString &value)
{
    contractNumber.setFindValue(value);
}

void FindObjectContract::setContractsSumFrom(const double &value)
{
    contractsSumFrom.setFindValue(value);
}

void FindObjectContract::setContractsSumTo(const double &value)
{
    contractsSumTo.setFindValue(value);
}

void FindObjectContract::setComment(const QString &value)
{
    comment.setFindValue(value);
}

void FindObjectContract::setStartDateFrom(const QDate &value)
{
    startDateFrom.setFindValue(value);
}

void FindObjectContract::setStartDateTo(const QDate &value)
{
    startDateTo.setFindValue(value);
}

void FindObjectContract::setEndDateFrom(const QDate &value)
{
    endDateFrom.setFindValue(value);
}

void FindObjectContract::setEndDateTo(const QDate &value)
{
    endDateTo.setFindValue(value);
}

void FindObjectContract::setProviderId(const uint &value)
{
    providerId.setFindValue(value);
}

void FindObjectContract::setSubdivisionId(const uint &value)
{
    subdivisionId.setFindValue(value);
}

void FindObjectContract::setResponsibleId(const uint &value)
{
    responsibleId.setFindValue(value);
}

void FindObjectContract::setSourceFinancingId(const uint &value)
{
    sourceFinancingId.setFindValue(value);
}

void FindObjectContract::setConclusionDateFrom(const QDate &value)
{
    conclusionDateFrom.setFindValue(value);
}

void FindObjectContract::setConclusionDateTo(const QDate &value)
{
    conclusionDateTo.setFindValue(value);
}

void FindObjectContract::setRegistrationDateFrom(const QDate &value)
{
    registrationDateFrom.setFindValue(value);
}

void FindObjectContract::setRegistrationDateTo(const QDate &value)
{
    registrationDateTo.setFindValue(value);
}

void FindObjectContract::setCompleteness(const bool &value)
{
    completeness.setFindValue(value);
}

